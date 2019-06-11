#include "Mixer.h"
#include <cmath>

#ifndef ENVELOPE_H
#define ENVELOPE_H

namespace tsal {

class Envelope {
  public:
    enum EnvelopeState {
      OFF,
      ATTACK,
      DECAY,
      SUSTAIN,
      RELEASE
    };
    Envelope();
    double getEnvelope();
    void updateState();
    void start();
    void stop();
  private:
    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
    bool stateIsTimed(); 
    EnvelopeState mState = OFF; 
    double mStateValue[5];
    unsigned mCurrentStateIndex = 0;
    unsigned mNextStateIndex = 0;
    double mEnvelopeValue = 0.0;
    double mMultiplier = 0.0;
};

}

#endif
