#pragma once

#include <cstdint>
#include <span>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Display {
public:
  Display() = default;
  ~Display();

  Display(const Display&) = delete;
  Display& operator=(const Display&) = delete;

  // Initialize the display with a title and scale factor
  [[nodiscard]] bool init(const char* title, int scale);
  // framebuffer is a span of 64x32 pixels, each pixel is either 0 (off) or 1 (on)
  void draw(std::span<const std::uint8_t> framebuffer);

private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
