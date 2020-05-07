#include "SoundFont.hpp"

namespace tsal {

SoundFont::SoundFont(std::string filename) {
  // mSoundFont = tsf_load_filename(filename.c_str());
  if (mSoundFont == nullptr) {
    std::cout << "Failed to load SoundFont: " << filename << std::endl;
    return;
  }
  mPresetRange = std::make_pair(0, getPresetCount());
}

SoundFont::~SoundFont() {
  // tsf_close(mSoundFont);
}

// void SoundFont::setMixer(Mixer* mixer) {
//   OutputDevice::updateContext(mContext)
//   tsf_set_output(mSoundFont, TSF_MONO, mContext.getSampleRate(), 0);
// }

void SoundFont::getOutput(AudioBuffer<float> &buffer) {
  // tsf_render_float(mSoundFont, buffer, buffer.size(), 0);
}

void SoundFont::play(double note, double velocity) {
  // tsf_note_on(mSoundFont, mPresetIndex, note, velocity/127.0);
}

void SoundFont::stop(double note) {
  // tsf_note_off(mSoundFont, mPresetIndex, note);
}

void SoundFont::reset() {
  // tsf_reset(mSoundFont);
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
  return 0;//tsf_get_presetindex(mSoundFont, bank, presetNumber);
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
  return 0; //tsf_get_presetcount(mSoundFont);
}
    
/** 
 * @brief Get the preset name from a preset index
 *
 * @param presetIndex
 */
std::string SoundFont::getPresetName(int presetIndex) {
  return ""; //std::string(tsf_get_presetname(mSoundFont, presetIndex));
}

/** 
 * @brief Get the preset name from a bank and preset number
 * See General MIDI standards
 *
 * @param bank
 * @param presetNumber
 */
std::string SoundFont::getPresetName(int bank, int presetNumber) {
  return ""; //std::string(tsf_bank_get_presetname(mSoundFont, bank, presetNumber));
}

} // namespace tsal
