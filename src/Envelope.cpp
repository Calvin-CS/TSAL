#include "Envelope.hpp" namespace tsal {
std::vector<ParameterManager::Parameter> Envelope::EnvelopeParameters
({
  { .name="Attack", .min=0.0, .max=100.0, .defaultValue=0.0, .exclusiveMin=true },
  { .name="Decay", .min=0.0, .max=100.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="Sustain", .min=0.0, .max=1.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="Release", .min=0.0, .max=100.0, .defaultValue=2.0, .exclusiveMin=true },
});
/**
 * @brief Increments the current state
 * 
 * Each state has its own set of unique properties. Those properties are updated here
 */
void Envelope::updateState() {
  mState = static_cast<EnvelopeState>((mState + 1) % 5);
  mCurrentStateIndex = 0;
  // OFF and SUSTAIN are indefinite so no need to set mNextStateIndex
  mNextStateIndex = stateIsTimed() ? getStateValue(mState) * mContext.getSampleRate() : 0;
  switch(mState) {
    case E_OFF:
      mEnvelopeValue = 0.0;
      break;
    case E_ATTACK:
      mEnvelopeValue = getStateValue(E_OFF);
      calculateMultiplier(mEnvelopeValue, 1.0, mNextStateIndex);
      break;
    case E_DECAY:
      mEnvelopeValue = 1.0;
      calculateMultiplier(mEnvelopeValue, getStateValue(E_SUSTAIN), mNextStateIndex);
      break;
    case E_SUSTAIN:
      mEnvelopeValue = getStateValue(E_SUSTAIN);
      break;
    case E_RELEASE:
      calculateMultiplier(mEnvelopeValue, getStateValue(E_OFF), mNextStateIndex);
      break;
  }  
}

double Envelope::getStateValue(EnvelopeState state) {
  // This assumes that parameters are ordered
  if (state == E_OFF) {
    return 0.0001;
  } else {
    return getParameter(state);
  }
}

/**
 * @brief Gets the current sample of the envelope
 * 
 * @return double A sample of the envelope
 */
double Envelope::getSample() {
  if (!mActive) {
    return 1.0;
  }
  if (stateIsTimed()) {
    if (mCurrentStateIndex >= mNextStateIndex) {
      updateState();
    }
    mCurrentStateIndex++;
    mEnvelopeValue *= mMultiplier;
  }
  // TODO: never figured out why, but occasionally the envelope Value skyrockets when in attack state. This is protect against anything ridiculous
  return std::min(1.0, mEnvelopeValue);
}

/**
 * @brief Calculate the multiplier that will be used to update the envelope value
 * 
 * Human sense are logarithmic, the envelope needs to change exponentially
 * This function calculates an appropriate multiplier that gets the envelope value 
 * from a start level to an end level in the number of specified samples (time)
 *
 * @param startLevel 
 * @param endLevel 
 * @param lengthInSamples
 */
void Envelope::calculateMultiplier(double startLevel, double endLevel, unsigned lengthInSamples) {
  mMultiplier = 1.0 + (std::log(endLevel) - std::log(startLevel)) / lengthInSamples;
}

/**
 * @brief starts the envelope in the attack state 
 * 
 */
void Envelope::start() {
  // Start the envelope in the attack state
  mState = E_OFF;
  updateState();
}

/**
 * @brief stops the envelope by transitioning into the release state
 * 
 */
void Envelope::stop() {
  mState = E_SUSTAIN;
  updateState();
}

/**
 * @brief Checks if the current state is one that is timed
 * 
 * Both off and sustain states can last indefinitely, while the others are timed
 * @return true 
 * @return false 
 */
bool Envelope::stateIsTimed() {
  return mState != E_OFF && mState != E_SUSTAIN;
}

/**
 * @brief Set all the envelope state values
 *
 * @param attackTime
 * @param decayTime
 * @param sustainLevel
 * @param releaseTime
 */
void Envelope::setEnvelope(double attackTime, double decayTime, double sustainLevel, double releaseTime) {
  setParameter(ATTACK, attackTime);
  setParameter(DECAY, decayTime);
  setParameter(SUSTAIN, sustainLevel);
  setParameter(RELEASE, releaseTime);
}

/**
 * @brief Set the attck time
 * 
 * @param attackTime 
 */
void Envelope::setAttackTime(double attackTime) {
  setParameter(ATTACK, attackTime);
}

/**
 * @brief Set the decay time
 * 
 * @param decayTime 
 */
void Envelope::setDecayTime(double decayTime) {
  setParameter(DECAY, decayTime);
}

/**
 * @brief Set the release time
 * 
 * @param releaseTime 
 */
void Envelope::setReleaseTime(double releaseTime) {
  setParameter(DECAY, releaseTime);
}

/**
 * @brief Set the sustain level
 * 
 * @param level 
 */
void Envelope::setSustainLevel(double level) {
  setParameter(SUSTAIN, level);
}

}
