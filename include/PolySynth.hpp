#ifndef POLYSYNTH_H
#define POLYSYNTH_H

#include "Synth.hpp"
#include "Oscillator.hpp"
#include "Instrument.hpp"

#define NUM_VOICES 1

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
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0);
    void stop(double note);
    void setMode(Oscillator::OscillatorMode mode);
 private:
    Synth* getInactiveVoice();
    Oscillator::OscillatorMode mMode;
    std::vector<Synth> mVoices;
    RouteDevice<Synth> mRoutedSynths;
};
  
}

#endif
