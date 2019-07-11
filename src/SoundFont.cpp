#include "SoundFont.hpp"
#include "Mixer.hpp"

namespace tsal {

SoundFont::SoundFont(std::string filename) {
  mSoundFont = tsf_load_filename(filename.c_str());
  tsf_set_output(mSoundFont, TSF_MONO, Mixer::getSampleRate(), 0); //sample rate
}

double SoundFont::getOutput() {
  float buffer[1];
  tsf_render_float(mSoundFont, buffer, 1, 0);
  if (buffer[0] > 1.0) 
    std::cout << buffer[0] << std::endl;

  return buffer[0] * SCALE;
}

void SoundFont::noteOn(unsigned note, double velocity) {
  tsf_note_on(mSoundFont, 1, note, velocity/127.0);
}

void SoundFont::noteOff(unsigned note) {
  tsf_note_off(mSoundFont, 1, note);
}

} // namespace tsal
