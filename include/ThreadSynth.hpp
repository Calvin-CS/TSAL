#ifndef THREADSYNTH_H
#define THREADSYNTH_H

#include "Instrument.hpp"
#include "Oscillator.hpp"
#include "MidiSequencer.hpp"
#include <condition_variable>

namespace tsal {

class ThreadSynth : public Oscillator {
  public:
    ThreadSynth();
    void noteOn(unsigned note, unsigned tick);
    void noteOff(unsigned note, unsigned tick);
    MidiSequencer* seq;
  private:
    void waitForEvent(unsigned tick);
    bool proceed();
};

}

#endif
