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
    SoundFont(Mixer* mixer, std::string filename);
    ~SoundFont();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0);
    void stop(double note);
    void channelNoteOn(int channel, unsigned note, double velocity = 100.0);
    void channelNoteOff(int channel, unsigned note);

    void reset();
    void setPreset(int presetIndex);
    void setPreset(std::string presetName);

    int getPresetIndex(int bank, int presetNumber);
    int getPresetIndex(std::string presetName);
    int getPresetCount();
    std::string getPresetName(int presetIndex);
    std::string getPresetName(int bank, int presetNumber);
  private:
    tsf* mSoundFont;
    int mPresetIndex = 0;
    Util::ParameterRange<int> mPresetRange;
};

}

#endif

#endif
