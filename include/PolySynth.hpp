#ifndef POLYSYNTH_H
#define POLYSYNTH_H

#include "Synth.hpp"
#include "Oscillator.hpp"
#include "Instrument.hpp"

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
    PolySynth(Mixer* mixer);
    PolySynth(PolySynth&& other) noexcept :
      Instrument(other.mMixer),
      mMode(std::move(other.mMode)),
      mVoices(std::move(other.mVoices)),
      mRoutedSynths(other.mMixer) {}
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0);
    void stop(double note);
    void setMode(Oscillator::OscillatorMode mode);
    PolySynth& operator=(const PolySynth& synth);
 private:
    Synth* getInactiveVoice();
    Oscillator::OscillatorMode mMode;
    std::vector<Synth> mVoices;
    RouteDevice<Synth> mRoutedSynths;
};
  
}

#endif
