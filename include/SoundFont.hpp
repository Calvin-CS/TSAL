#ifndef SOUNDFONT_H
#define SOUNDFONT_H

#include "Instrument.hpp"

#ifndef TSF_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include "tsf.h"


namespace tsal {

/** @class SoundFont
 * @brief A SoundFont 2 synthesizer that can sf2 files
 *
 * SoundFonts seem to be the easiest way to synthesize real instruments. The
 * SoundFont class uses the TinySoundFont library to load and play sf2 files.
 *
 * Useful links:
 * - https://github.com/schellingb/TinySoundFont/
 * - http://www.synthfont.com/soundfonts.html
 */
class SoundFont : public Instrument {
  public:
    SoundFont(std::string filename) {
      mSoundFont = tsf_load_filename(filename.c_str());
      if (mSoundFont == nullptr) {
        std::cout << "Failed to load SoundFont: " << filename << std::endl;
        return;
      }
    };
    virtual ~SoundFont() {
      tsf_close(mSoundFont);
    };
    virtual void getOutput(AudioBuffer<float> &buffer) override {
      return;
      tsf_render_float(mSoundFont, buffer.getRawPointer(), buffer.size(), 0);
    };
    virtual void play(double note, double velocity = 100.0) override {
      tsf_note_on(mSoundFont, mPresetIndex, note, velocity/127.0);
    };
    virtual void stop(double note) override {
      tsf_note_off(mSoundFont, mPresetIndex, note);
    };
    void channelNoteOn(int channel, unsigned note, double velocity = 100.0) {
    };
    void channelNoteOff(int channel, unsigned note) {};

    void reset() {};
    void setPreset(int presetIndex) {
      mPresetIndex = presetIndex;
    };
    void setPreset(std::string presetName) {
      setPreset(getPresetIndex(presetName));
    };

    int getPresetIndex(int bank, int presetNumber) {
      return tsf_get_presetindex(mSoundFont, bank, presetNumber);
    };
    int getPresetIndex(std::string presetName) {
      for (int i = 0; i < getPresetCount(); i++) {
        if (presetName == getPresetName(i)) {
          return i;
        }
      }
      return -1;
    };
    int getPresetCount() {
      return tsf_get_presetcount(mSoundFont);
    };
    std::string getPresetName(int presetIndex) {
      return std::string(tsf_get_presetname(mSoundFont, presetIndex));
    };
    std::string getPresetName(int bank, int presetNumber) {
      return std::string(tsf_bank_get_presetname(mSoundFont, bank, presetNumber));
    };
  private:
    tsf* mSoundFont;
    int mPresetIndex = 0;
};

}

#endif

#endif
