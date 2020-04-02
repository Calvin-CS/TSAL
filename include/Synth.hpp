#ifndef SYNTH_H
#define SYNTH_H

#include "Oscillator.hpp"
#include "Envelope.hpp"
#include "Instrument.hpp"
#include "MidiNotes.hpp"
#include "Sequencer.hpp"

namespace tsal {

/** @class Synth
 * @brief A monophnoic synthesizer
 * 
 * Synth uses the oscillator and envelope classes to create a basic 
 * monophonic synthesizer that can be used to play midinotes
 */
class Synth : public Instrument {
  public:
    Synth();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    virtual void play(double note, double velocity = 100.0) override;
    virtual void stop(double note = MidiNote::A0) override;
    void setVelocity(double velocity);
    void setMode(Oscillator::OscillatorMode mode) { mOscillator.setMode(mode); };
    void setEnvelopeActive(bool active = true) { mEnvelope.setActive(active); };
    void setEnvelope(double attackTime, double decayTime, double sustainLevel,
                     double releaseTime) {
      mEnvelope.setActive();
      mEnvelope.setEnvelope(attackTime, decayTime, sustainLevel, releaseTime);
    };

    double getNote() const;
    
    virtual void updateContext(const Context& context) override {
      OutputDevice::updateContext(context);
      mOscillator.updateContext(context);
      mEnvelope.updateContext(context);
    }

  private:
    Oscillator mOscillator;
    Envelope mEnvelope;
    double mVelocity = 0.0;
    double mNote = 0.0;
    
    static Util::ParameterRange<double> mVelocityRange;
}; 

}

#endif 
