#include "SoundFont.hpp"
#include "Mixer.hpp"

namespace tsal {

SoundFont::SoundFont(std::string filename) {
  mSoundFont = std::unique_ptr<tsf>(tsf_load_filename(filename.c_str()));
  if (mSoundFont == nullptr) {
    std::cout << "Failed to load SoundFont: " << filename << std::endl;
    return;
  }
  mPresetRange = std::make_pair(0, getPresetCount());
}

SoundFont::~SoundFont() {
  tsf_close(mSoundFont.get());
}

void SoundFont::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  tsf_set_output(mSoundFont.get(), TSF_MONO, getMixer()->getSampleRate(), 0);
}

double SoundFont::getOutput() {
  float buffer[1];
  tsf_render_float(mSoundFont.get(), buffer, 1, 0);
  return buffer[0] * mAmp;
}

void SoundFont::noteOn(double note, double velocity) {
  tsf_note_on(mSoundFont.get(), mPresetIndex, note, velocity/127.0);
}

void SoundFont::noteOff(double note) {
  tsf_note_off(mSoundFont.get(), mPresetIndex, note);
}

void SoundFont::reset() {
  tsf_reset(mSoundFont.get());
}

/** 
 * @brief Set the preset (voice) from a preset index
 *
 * @param presetIndex
 */
void SoundFont::setPreset(int presetIndex) {
  mPresetIndex = Util::checkParameterRange("SoundFont: setPreset", presetIndex, mPresetRange);
}

/** 
 * @brief Set the preset (voice) from a preset name
 *
 * @param presetName
 */
void SoundFont::setPreset(std::string presetName) {
  setPreset(getPresetIndex(presetName));
}

/** 
 * @brief Get the preset index from a bank and preset number
 * See General MIDI standards
 *
 * @param bank
 * @param presetNumber
 */
int SoundFont::getPresetIndex(int bank, int presetNumber) {
  return tsf_get_presetindex(mSoundFont.get(), bank, presetNumber);
}

/** 
 * @brief Get the preset index from a preset name
 *
 * @param bank
 * @param presetNumber
 */
int SoundFont::getPresetIndex(std::string presetName) {
  for (int i = 0; i < getPresetCount(); i++) {
    if (presetName == getPresetName(i)) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Get the number of presets in the soundfont
 */
int SoundFont::getPresetCount() {
  return tsf_get_presetcount(mSoundFont.get());
}
    
/** 
 * @brief Get the preset name from a preset index
 *
 * @param presetIndex
 */
std::string SoundFont::getPresetName(int presetIndex) {
  return std::string(tsf_get_presetname(mSoundFont.get(), presetIndex));
}

/** 
 * @brief Get the preset name from a bank and preset number
 * See General MIDI standards
 *
 * @param bank
 * @param presetNumber
 */
std::string SoundFont::getPresetName(int bank, int presetNumber) {
  return std::string(tsf_bank_get_presetname(mSoundFont.get(), bank, presetNumber));
}

} // namespace tsal
