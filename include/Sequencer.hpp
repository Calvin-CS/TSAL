#ifndef MIDISEQUENCER_H
#define MIDISEQUENCER_H

#include "Util.hpp"
#include <condition_variable>
#include <functional>
#include <vector>
#include <algorithm>
#include <queue>

namespace tsal {

// Forward declaration of Mixer
class Mixer;

/** @class Sequencer
 * @brief A sequencer that handles the scheduling of events
 * 
 * Sequencer handles the real-time scheduling of the process
 * based upon BPM and PPQ parameters
 */
class Sequencer {
  public:
    void tick();
    void start();
    void stop();
    void setSampleRate(unsigned sampleRate) { mSampleRate = sampleRate; };
    void setTick(unsigned tick);
    void setBPM(unsigned bpm);
    void setPPQ(unsigned ppq);
    void schedule(std::function<void ()> callback, Timing::NoteScale scale, unsigned duration = 1);
    unsigned getTick() const;
    unsigned getTicksInNote(Timing::NoteScale note) const;
    /*
     * A helper class that wraps a tick value and callback for event scheduling 
     */
    struct Event {
        Event(unsigned t, std::function<void ()> f) {
          tick = t;
          callback = f;
        }
        // A compare function for the sorting of the priority queue
        struct compare {
            bool operator()(const std::unique_ptr<Event>& lhs, const std::unique_ptr<Event>& rhs) {
              return lhs->tick > rhs->tick;
            }
        };
        unsigned tick;
        std::function<void ()> callback;
    };
    
  private:
    std::priority_queue<std::unique_ptr<Event>, std::vector<std::unique_ptr<Event>>, Event::compare> mEventQueue;
    void setSamplesPerTick();
    unsigned mSampleTime = 0;
    unsigned mTick = 0;


    unsigned mPPQ = 240;
    unsigned mBPM = 100;
    unsigned mSampleRate = 0;
    double mSamplesPerTick = 0.0;

    static Util::ParameterRange<unsigned> mBPMRange;
    static Util::ParameterRange<unsigned> mPPQRange;
};

}
#endif
