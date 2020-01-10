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
    ThreadSynth(const Context& context);
    void play(double note, Timing::TimeScale scale, unsigned multiplier);
    void play(double note, Timing::NoteScale scale, unsigned multiplier);
    void stop(Timing::TimeScale scale, unsigned multiplier);
    void stop(Timing::NoteScale scale, unsigned multiplier);
    void stop() { Synth::stop(); };
  private:
    void notify();
    void lock(Timing::NoteScale, unsigned multiplier);
    std::mutex mMutex;
    std::condition_variable mCondition;
};

}

#endif
