#ifndef MIDISEQUENCER_H
#define MIDISEQUENCER_H

#include "Util.hpp"

namespace tsal {

class MidiSequencer {
  public:
    MidiSequencer();
    void tick();
    void start();
    void stop();
    void setBPM(unsigned bpm);
  private:
    unsigned mSampleTime = 0;
    unsigned mTick = 0;

    unsigned mPPQ = 480;
    unsigned mBPM = 120;
    double mSamplesPerTick;

    static ParameterRange<unsigned> mBPMRange;
};

}
#endif
