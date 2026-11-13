#include "chip8.h"

#include <print>

Chip8::Chip8() {
  reset();
}

void Chip8::reset() {
  // TODO: Implement reset logic
  // Clear all state
  // Set program counter to PROGRAM_START_ADDRESS
  // Copy font to FONTSET_START_ADDRESS
}

bool Chip8::load_rom(const std::span<const std::uint8_t> rom) {
  std::print("Loading ROM of size {}", rom.size());
  // TODO: Implement ROM loading logic
  // Check if ROM fits after PROGRAM_START_ADDRESS
  // Copy ROM into memory at PROGRAM_START_ADDRESS
  return true;
}

void Chip8::step() {
  // TODO: Implement instruction fetch, decode, and execute logic
}

void Chip8::tick_timers() {
  // TODO: decrement delay timer and sound timer if they are greater than zero
}

void Chip8::set_key([[maybe_unused]] std::uint8_t key, [[maybe_unused]] bool pressed) {
  // TODO: Implement key press/release logic (0x0 to 0xF)
}
