#include "Mixer.h"
#include <cmath>

#ifndef ENVELOPE_H
#define ENVELOPE_H

namespace tsal {

/** @class Envelope
 * @brief An sound envelope that can be used to change a sound over time
 * 
 * A 4 stage envelope transitions from attack, to decay, to sustain, and then to release. It achieves
 * a smoother sound when overlayed on an instrument
 * Implementation adapted from http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
 */
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
    void calculateMultiplier(double startLevel, double endLevel, unsigned lengthInSamples);
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
