#ifndef SYNTH_H
#define SYNTH_H

#include "Oscillator.hpp"
#include "Envelope.hpp"
#include "Instrument.hpp"
#include "MidiNotes.hpp"

namespace tsal {

/** @class Synth
 * @brief A monophnoic synthesizer
 * 
 * Synth uses the oscillator and envelope classes to create a basic 
 * monophonic synthesizer that can be used to play midinotes
 */
class Synth : public Instrument {
  public:
    virtual double getOutput() override;
    virtual void noteOn(double note, double velocity = 100.0) override;
    virtual void noteOff(double note = A0) override;
    void setVelocity(double velocity);
    void setMode(Oscillator::OscillatorMode mode) { mOscillator.setMode(mode); };
    void setEnvelopeActive(bool active = true) { mEnvelope.setActive(active); };
    void setEnvelope(double attackTime, double decayTime, double sustainLevel,
                     double releaseTime) {
      mEnvelope.setEnvelope(attackTime, decayTime, sustainLevel, releaseTime);
    };

    double getNote() const;
    
    virtual void setMixer(Mixer* mixer) override {
      OutputDevice::setMixer(mixer);
      mOscillator.setMixer(mixer);
      mEnvelope.setMixer(mixer);
    }

  private:
    Oscillator mOscillator;
    Envelope mEnvelope;
    double mVelocity;
    double mNote = 0.0;
    
    static Util::ParameterRange<double> mVelocityRange;
}; 

}

#endif 
