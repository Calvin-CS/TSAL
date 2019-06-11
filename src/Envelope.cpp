#include "Envelope.h"

namespace tsal {

Envelope::Envelope() {
  mStateValue[OFF] = 0.0001;
  mStateValue[ATTACK] = 0.001;
  mStateValue[DECAY] = 0.5;
  mStateValue[SUSTAIN] = 0.5;
  mStateValue[RELEASE] = 1.0; 
}

void Envelope::updateState() {
  mState = static_cast<EnvelopeState>((mState + 1) % 5);
  mCurrentStateIndex = 0;
  // OFF and SUSTAIN are indefinite so no need to set mNextStateIndex
  mNextStateIndex = stateIsTimed() ? mStateValue[mState] * Mixer::getSampleRate() : 0;
  switch(mState) {
    case OFF:
      mEnvelopeValue = 0.0;
      break;
    case ATTACK:
      mEnvelopeValue = mStateValue[OFF];
      calculateMultiplier(mEnvelopeValue, 1.0, mNextStateIndex);
      break;
    case DECAY:
      mEnvelopeValue = 1.0;
      calculateMultiplier(mEnvelopeValue, mStateValue[SUSTAIN], mNextStateIndex);
      break;
    case SUSTAIN:
      mEnvelopeValue = mStateValue[SUSTAIN];
      break;
    case RELEASE:
      calculateMultiplier(mEnvelopeValue, mStateValue[OFF], mNextStateIndex);
      break;
  }  
}

double Envelope::getEnvelope() {
  if (stateIsTimed()) {
    if (mCurrentStateIndex == mNextStateIndex) {
      updateState();
    }
    mCurrentStateIndex++;
    mEnvelopeValue *= mMultiplier;
  }
  return mEnvelopeValue;
}

void Envelope::calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples) {
  mMultiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

void Envelope::start() {
  // Start the envelope in the attack state
  mState = OFF;
  updateState();
}

void Envelope::stop() {
  if (mState != OFF) {
    updateState();
  }
}

bool Envelope::stateIsTimed() {
  return mState != OFF && mState != SUSTAIN;
}

}
