#ifndef POLYSYNTH_H
#define POLYSYNTH_H

#include "Synth.hpp"
#include "Oscillator.hpp"
#include "Instrument.hpp"
#include "RouteDevice.hpp"

#define NUM_VOICES 20

namespace tsal {

/** @class PolySynth
 * @brief A polyphonic synthesizer
 *
 * PolySynth uses multiple Synths to create a polyphonic 
 * synthesizer that can handle multiple notes being played
 * at the same time
 */
class PolySynth : public Instrument {
  public:
    PolySynth() = default;
    PolySynth(PolySynth&& other) noexcept :
      mMode(std::move(other.mMode)),
      mVoices(std::move(other.mVoices)) {
      for (unsigned i = 0; i < mVoices.size(); i++) {
        mVoices[i].setActive(false);
        mVoices[i].setVolume(0.3);
        mRoutedSynths.add(mVoices[i]);
      }
      updateContext(other.mContext);
    }
    PolySynth();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0);
    void stop(double note);
    void setMode(Oscillator::OscillatorMode mode);
    PolySynth& operator=(const PolySynth& synth);
    virtual void updateContext(const Context& context) override;
 private:
    Synth* getInactiveVoice();
    Oscillator::OscillatorMode mMode;
    std::vector<Synth> mVoices;
    RouteDevice<Synth> mRoutedSynths;
};
  
}

#endif
