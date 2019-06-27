#ifndef MIDISEQUENCER_H
#define MIDISEQUENCER_H

#include "Util.hpp"
#include <condition_variable>
#include <functional>

namespace tsal {

class MidiSequencer {
  public:
    void tick();
    void start();
    void stop();
    void setBPM(unsigned bpm);
    void setPPQ(unsigned ppq);
    unsigned getTick() const;
    // Testings
    std::mutex mutex;
    std::condition_variable cond;
    static unsigned mTick;
  private:
    void setSamplesPerTick();
    unsigned mSampleTime = 0;


    unsigned mPPQ = 240;
    unsigned mBPM = 120;
    double mSamplesPerTick;

    static ParameterRange<unsigned> mBPMRange;
};

}
#endif
