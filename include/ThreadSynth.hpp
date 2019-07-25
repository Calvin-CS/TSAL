#ifndef THREADSYNTH_H
#define THREADSYNTH_H

#include "Sequencer.hpp"
#include "Synth.hpp"
#include <condition_variable>

namespace tsal {

/** @class ThreadSynth
 * @brief A threaded audio synthesizer
 * 
 * A more specific implementation of the Synth class that dedicates the synth's
 * thread as the means to schedule events and timings for notes. This class
 * is mainly used for multithreading examples and doesn't really have
 * any other meaningful applications
 */
class ThreadSynth : public Synth {
  public:
    ThreadSynth(Mixer* mixer);
    virtual void noteOnTest(double note, double velocity, unsigned tick) ;
    virtual void noteOffTest(double note, unsigned tick) ;
};

}

#endif
