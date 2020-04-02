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
    virtual void play(double note, double velocity) override {
      Synth::play(note, velocity);
    };
    virtual void stop(double note = MidiNote::A0) override {
      Synth::stop();
    };
    void play(double note, Timing::TimeScale scale, unsigned duration);
    void stop(Timing::TimeScale scale, unsigned multiplier);
};

}

#endif
