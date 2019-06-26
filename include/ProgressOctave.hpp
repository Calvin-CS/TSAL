#ifndef PROGRESSOCTAVE_H
#define PROGRESSOCTAVE_H

#include "Oscillator.hpp"
#include "Instrument.hpp"
#include "RouteDevice.hpp"
#include <vector>

namespace tsal {

class ProgressOctave : public Instrument {
  public:
    ProgressOctave(unsigned startNote, unsigned problemSize, unsigned numWorkers);
    virtual double getOutput() override;
    void update(unsigned id);
  private:
    RouteDevice<Oscillator> mOscillators;
    double mStepValue;
};
  
}

#endif
