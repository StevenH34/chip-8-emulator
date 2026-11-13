#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdint>
#include <optional>
#include <vector>

#include "../core/chip8.h"
#include "audio.h"
#include "display.h"
#include "input.h"

namespace {
  constexpr int FRAMES_PER_SECOND = 60;
  constexpr int INSTRUCTIONS_PER_FRAME = 12; // 720 instructions per second at 60 Hz
  constexpr int WINDOW_SCALE = 10; // Scale factor for the window size

  constexpr std::uint64_t FRAME_NS = SDL_NS_PER_SECOND / FRAMES_PER_SECOND;
  // Cap on how much time a single loop iteration may catch up on, so a long
  // stall (window drag, debugger break) doesn't cause a burst of fast-forward.
  constexpr std::uint64_t MAX_CATCH_UP_NS = 5 * FRAME_NS;

  std::optional<std::vector<std::uint8_t>> read_file(const char* path) {
    std::size_t size = 0;
    void* data = SDL_LoadFile(path, &size);
    if (!data) {
      SDL_Log("Failed to load file %s: %s", path, SDL_GetError());
      return std::nullopt;
    }
    const auto* bytes = static_cast<const std::uint8_t*>(data);
    std::vector<std::uint8_t> contents(bytes, bytes + size);
    SDL_free(data);
    return contents;
  }

  int run(const char* rom_path) {
    const auto rom = read_file(rom_path);
    if (!rom) return 1;

    Chip8 chip8;
    if (!chip8.load_rom(*rom)) {
      SDL_Log("Failed to load ROM: %s", rom_path);
      return 1;
    }

    Display display;
    if (!display.init("CHIP-8", WINDOW_SCALE)) return 1;

    Audio audio;
    if (!audio.init()) {
      SDL_Log("Audio unavailable, continuing without sound: %s", SDL_GetError());
    }

    std::uint64_t accumulator = 0;
    std::uint64_t last_time = SDL_GetTicksNS();

    bool running = true;
    while (running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_EVENT_QUIT:
            running = false;
            break;
          case SDL_EVENT_KEY_DOWN:
          case SDL_EVENT_KEY_UP:
            if (auto key = key_map(event.key.scancode)) {
              chip8.set_key(*key, event.key.down);
            }
            break;
        }
      }

      const std::uint64_t now = SDL_GetTicksNS();
      accumulator += now - last_time;
      last_time = now;
      if (accumulator > MAX_CATCH_UP_NS) accumulator = MAX_CATCH_UP_NS;

      const bool stepped = accumulator >= FRAME_NS;
      while (accumulator >= FRAME_NS) {
        for (int i = 0; i < INSTRUCTIONS_PER_FRAME; ++i) {
          chip8.step();
        }
        chip8.tick_timers();
        accumulator -= FRAME_NS;
      }

      audio.set_active(chip8.sound_active());

      if (stepped) {
        display.draw(chip8.framebuffer());
      } else {
        // Ahead of schedule (vsync off, or a high-refresh display): sleep until
        // the next frame is due instead of spinning.
        SDL_DelayPrecise(FRAME_NS - accumulator);
      }
    }

    return 0;
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    SDL_Log("Usage: %s <path_to_rom>", argv[0]);
    return 1;
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }
  // Audio is optional: a machine with no audio device should still run games.
  if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
    SDL_Log("Audio subsystem init failed: %s", SDL_GetError());
  }

  const int result = run(argv[1]);
  SDL_Quit();
  return result;
}
