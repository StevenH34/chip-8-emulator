#pragma once

#include <SDL3/SDL_scancode.h>

#include <cstdint>
#include <optional>

// Returns the CHIP-8 key (0x0–0xF) for a scancode, or nullopt if it isn't mapped.
// The 1234 / QWER / ASDF / ZXCV block maps to the keypad:
//   1 2 3 C
//   4 5 6 D
//   7 8 9 E
//   A 0 B F
constexpr std::optional<std::uint8_t> key_map(SDL_Scancode scancode) {
  switch (scancode) {
  case SDL_SCANCODE_1:
    return 0x1;
  case SDL_SCANCODE_2:
    return 0x2;
  case SDL_SCANCODE_3:
    return 0x3;
  case SDL_SCANCODE_4:
    return 0xC;
  case SDL_SCANCODE_Q:
    return 0x4;
  case SDL_SCANCODE_W:
    return 0x5;
  case SDL_SCANCODE_E:
    return 0x6;
  case SDL_SCANCODE_R:
    return 0xD;
  case SDL_SCANCODE_A:
    return 0x7;
  case SDL_SCANCODE_S:
    return 0x8;
  case SDL_SCANCODE_D:
    return 0x9;
  case SDL_SCANCODE_F:
    return 0xE;
  case SDL_SCANCODE_Z:
    return 0xA;
  case SDL_SCANCODE_X:
    return 0x0;
  case SDL_SCANCODE_C:
    return 0xB;
  case SDL_SCANCODE_V:
    return 0xF;
  default:
    return std::nullopt;
  }
}