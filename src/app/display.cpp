#include "display.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <array>

#include "../core/chip8.h"

namespace {
  // SDL APIs take int dimensions; convert once here at the SDL boundary
  constexpr int DISPLAY_WIDTH = static_cast<int>(Chip8::DISPLAY_WIDTH);
  constexpr int DISPLAY_HEIGHT = static_cast<int>(Chip8::DISPLAY_HEIGHT);
  constexpr int PITCH = DISPLAY_WIDTH * static_cast<int>(sizeof(std::uint32_t));
  constexpr std::uint32_t PIXEL_ON = 0xFFFFFFFF;  // White
  constexpr std::uint32_t PIXEL_OFF = 0x000000FF; // Black
} // namespace

Display::~Display() {
  if (texture_)
    SDL_DestroyTexture(texture_);
  if (renderer_)
    SDL_DestroyRenderer(renderer_);
  if (window_)
    SDL_DestroyWindow(window_);
}

bool Display::init(const char* title, int scale) {
  // Create SDL window and renderer
  if (!SDL_CreateWindowAndRenderer(title, DISPLAY_WIDTH * scale, DISPLAY_HEIGHT * scale,
                                   SDL_WINDOW_RESIZABLE, &window_, &renderer_)) {
    SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
    return false;
  }

  SDL_SetRenderVSync(renderer_, 1);
  SDL_SetRenderLogicalPresentation(renderer_, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                               DISPLAY_WIDTH, DISPLAY_HEIGHT);
  if (!texture_) {
    SDL_Log("SDL_CreateTexture failed: %s", SDL_GetError());
    return false;
  }

  SDL_SetTextureScaleMode(texture_, SDL_SCALEMODE_NEAREST);
  return true;
}

void Display::draw(const std::span<const std::uint8_t> framebuffer) {
  // Convert framebuffer (0 or 1) to pixel colors (PIXEL_ON or PIXEL_OFF)
  std::array<std::uint32_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> pixels{};
  // Ensure we don't exceed the framebuffer size
  const std::size_t count = std::min(pixels.size(), framebuffer.size());

  // Fill the pixels array based on the framebuffer values
  for (std::size_t i = 0; i < count; ++i) {
    pixels[i] = framebuffer[i] ? PIXEL_ON : PIXEL_OFF;
  }
  // Update the texture with the pixel data
  SDL_UpdateTexture(texture_, nullptr, pixels.data(), PITCH);
  // Render the texture to the screen
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  // Clear the renderer
  SDL_RenderClear(renderer_);
  // Copy the texture to the renderer
  SDL_RenderTexture(renderer_, texture_, nullptr, nullptr);
  // Present the renderer to the screen
  SDL_RenderPresent(renderer_);
}
