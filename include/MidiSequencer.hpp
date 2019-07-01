#ifndef MIDISEQUENCER_H
#define MIDISEQUENCER_H

#include "Util.hpp"
#include <condition_variable>
#include <functional>
#include <vector>
#include <algorithm>

namespace tsal {

class MidiSequencer {
  public:
    void tick();
    void start();
    void stop();
    void setBPM(unsigned bpm);
    void setPPQ(unsigned ppq);
    unsigned getTick() const;
    void waitForTick(unsigned tick);
    // Testings
    std::mutex mutex; 
    std::condition_variable cond;
  private:
    std::vector<unsigned> mTickEvents;
    void setSamplesPerTick();
    unsigned mSampleTime = 0;
    unsigned mTick;


    unsigned mPPQ;
    unsigned mBPM;
    double mSamplesPerTick;

    static ParameterRange<unsigned> mBPMRange;
};

}
#endif
