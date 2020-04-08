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
    PolySynth(PolySynth&& other) noexcept :
      mMix(std::move(other.mMix)),
      mVoices(std::move(other.mVoices)) {
      for (unsigned i = 0; i < mVoices.size(); i++) {
        mVoices[i].stop(0.0);
      }
      updateContext(other.mContext);
    }
    PolySynth();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0) override;
    void stop(double note) override;
    void setMode(Oscillator::OscillatorMode mode);
    PolySynth& operator=(const PolySynth& synth);
    virtual void updateContext(const Context& context) override;
 private:
    class Voice : public Instrument {
      public:
        Voice() {
          mOsc2.setMode(Oscillator::SAW);
          mFilter.setMode(Filter::BANDPASS);
          mFilter.setCutoff(0.1);
        }
        double getSample(double mix);
        void play(double note, double velocity) override;
        void stop(double note = MidiNote::A0) override;
        virtual void updateContext(const Context& context) override; 
        double getNote() { return mOsc1.getNote(); };
      private:
        Oscillator mOsc1;
        Oscillator mOsc2;
        Filter mFilter;
        Envelope mEnvelope;
        double mVelocity = 100.0;
        unsigned mNote = 0.0;
    };
    Voice* getInactiveVoice();
    double mMix = 0.05;
    std::vector<Voice> mVoices;
};
  
}

#endif
