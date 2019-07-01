#ifndef THREADSYNTH_H
#define THREADSYNTH_H

#include "MidiSequencer.hpp"
#include "Synth.hpp"
#include <condition_variable>

namespace tsal {

class ThreadSynth : public Synth {
  public:
    void noteOn(unsigned note, unsigned tick);
    void noteOff(unsigned note, unsigned tick);
  private:
    void waitForEvent(unsigned tick);
};

}

#endif
