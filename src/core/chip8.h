#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

class Chip8 {
public:
  // Constants
  static constexpr std::size_t MEMORY_SIZE = 4096;              // 4K memory
  static constexpr std::uint16_t PROGRAM_START_ADDRESS = 0x200; // Programs start at 0x200
  static constexpr std::uint16_t FONTSET_START_ADDRESS = 0x50;  // Fontset starts at 0x50
  static constexpr std::size_t DISPLAY_WIDTH = 64;
  static constexpr std::size_t DISPLAY_HEIGHT = 32;

  // Constructor
  Chip8();

  void reset();
  bool load_rom(std::span<const std::uint8_t> rom);
  void step();
  void tick_timers();
  void set_key(std::uint8_t key, bool pressed);
  [[nodiscard]] std::span<const std::uint8_t> framebuffer() const { return display_; }
  [[nodiscard]] bool sound_active() const { return st_ > 0; }

private:
  // Memory
  std::array<std::uint8_t, MEMORY_SIZE> memory_{}; // 4K memory

  // Registers
  std::array<std::uint8_t, 16> V_{};         // General purpose registers V0 to VF
  std::uint16_t I_ = 0;                      // Index register
  std::uint16_t pc_ = PROGRAM_START_ADDRESS; // Program counter

  // Timers
  std::uint8_t dt_ = 0; // Delay timer
  std::uint8_t st_ = 0; // Sound timer

  // Stack
  std::array<std::uint16_t, 16> stack_{}; // Call stack
  std::uint8_t sp_ = 0;                   // Stack pointer

  // Input
  std::array<bool, 16> keys_{}; // Key states (0 = not pressed, 1 = pressed)

  // Display
  std::array<std::uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> display_{}; // 0 = off, 1 = on
};
