#include "audio.h"

Audio::~Audio() {
  SDL_DestroyAudioStream(audio_stream_);
}

bool Audio::init() {
  // TODO: SDL_OpenAudioDeviceStream
  return true;
}

void Audio::set_active([[maybe_unused]] bool on) {
  // Activate or deactivate the audio system here
}
