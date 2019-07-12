#include "SoundFont.hpp"
#include "Mixer.hpp"

namespace tsal {

SoundFont::SoundFont(std::string filename) {
  mSoundFont = tsf_load_filename(filename.c_str());
  if (mSoundFont == NULL) {
    std::cout << "Failed to load SoundFont: " << filename << std::endl;
    return;
  }
  mPresetRange = std::make_pair(0, getPresetCount());
}

SoundFont::~SoundFont() {
  tsf_close(mSoundFont);
}

void SoundFont::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  tsf_set_output(mSoundFont, TSF_MONO, mMixer->getSampleRate(), 0);
}

double SoundFont::getOutput() {
  float buffer[1];
  tsf_render_float(mSoundFont, buffer, 1, 0);
  return buffer[0] * mAmp * SCALE;
}

void SoundFont::noteOn(unsigned note, double velocity) {
  tsf_note_on(mSoundFont, mPresetIndex, note, velocity/127.0);
}

void SoundFont::noteOff(unsigned note) {
  tsf_note_off(mSoundFont, mPresetIndex, note);
}

void SoundFont::reset() {
  tsf_reset(mSoundFont);
}

void SoundFont::setPreset(int presetIndex) {
  mPresetIndex = checkParameterRange("SoundFont: setPreset", presetIndex, mPresetRange);
}

void SoundFont::setPreset(std::string presetName) {
  setPreset(getPresetIndex(presetName));
}

int SoundFont::getPresetIndex(int bank, int presetNumber) {
  return tsf_get_presetindex(mSoundFont, bank, presetNumber);
}

int SoundFont::getPresetIndex(std::string presetName) {
  for (int i = 0; i < getPresetCount(); i++) {
    if (presetName == getPresetName(i)) {
      return i;
    }
  }
  return -1;
}

int SoundFont::getPresetCount() {
  return tsf_get_presetcount(mSoundFont);
}
    
std::string SoundFont::getPresetName(int presetIndex) {
  return std::string(tsf_get_presetname(mSoundFont, presetIndex));
}

std::string SoundFont::getPresetName(int bank, int presetNumber) {
  return std::string(tsf_bank_get_presetname(mSoundFont, bank, presetNumber));
}

} // namespace tsal
