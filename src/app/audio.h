#pragma once

#include <SDL3/SDL_audio.h>

class Audio {
public:
  Audio() = default;
  ~Audio();
  Audio(const Audio&) = delete;
  Audio& operator=(const Audio&) = delete;

  [[nodiscard]] bool init();
  void set_active(bool on);

private:
  SDL_AudioStream* audio_stream_ = nullptr;
};
