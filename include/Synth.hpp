#ifndef SYNTH_H
#define SYNTH_H

#include "Oscillator.hpp"
#include "Envelope.hpp"
#include "Instrument.hpp"

namespace tsal {

class Synth : public Instrument {
  public:
    virtual double getOutput() override;
    virtual void noteOn(unsigned note, double velocity = 100) override;
    virtual void noteOff(unsigned note) override;
  private:
    Oscillator mOscillator;
    Envelope mEnvelope;
}; 

}

#endif 
