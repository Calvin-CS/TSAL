#include "Envelope.hpp"

namespace tsal {

// Ensures that a parameter is never actually set to 0. A value of 0
// does not work with calculateMultiplier function, so just set a really
// small value when 0 is specified
template <typename Item>
Item checkParameterRangeWithMax(const std::string& name, Item value, std::pair<Item, Item> range) {
  return std::max(Util::checkParameterRange(name, value, range), MIN_VALUE);
}

Envelope::Envelope(Mixer* mixer) : OutputDevice(mixer) {
  mStateValue[OFF] = MIN_VALUE;
  mStateValue[ATTACK] = 0.01;
  mStateValue[DECAY] = 0.5;
  mStateValue[SUSTAIN] = 0.5;
  mStateValue[RELEASE] = 2.0;
}

/**
 * @brief Increments the current state
 * 
 * Each state has its own set of unique properties. Those properties are updated here
 */
void Envelope::updateState() {
  mState = static_cast<EnvelopeState>((mState + 1) % 5);
  mCurrentStateIndex = 0;
  // OFF and SUSTAIN are indefinite so no need to set mNextStateIndex
  mNextStateIndex = stateIsTimed() ? mStateValue[mState] * mMixer->getSampleRate() : 0;
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
  mState = OFF;
  updateState();
}

/**
 * @brief stops the envelope by transitioning into the release state
 * 
 */
void Envelope::stop() {
  mState = SUSTAIN;
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
  return mState != OFF && mState != SUSTAIN;
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
  setAttackTime(attackTime);
  setDecayTime(decayTime);
  setSustainLevel(sustainLevel);
  setReleaseTime(releaseTime);
}

/**
 * @brief Set the attck time
 * 
 * @param attackTime 
 */
void Envelope::setAttackTime(double attackTime) {
  mStateValue[ATTACK] = checkParameterRangeWithMax("Envelope: AttackTime", attackTime, mTimeRange);
}

/**
 * @brief Set the decay time
 * 
 * @param decayTime 
 */
void Envelope::setDecayTime(double decayTime) {
  mStateValue[DECAY] = checkParameterRangeWithMax("Envelope: DecayTime", decayTime, mTimeRange);
}

/**
 * @brief Set the release time
 * 
 * @param releaseTime 
 */
void Envelope::setReleaseTime(double releaseTime) {
  mStateValue[RELEASE] = checkParameterRangeWithMax("Envelope: ReleaseTime", releaseTime, mTimeRange);
}

/**
 * @brief Set the sustain level
 * 
 * @param level 
 */
void Envelope::setSustainLevel(double level) {
  mStateValue[SUSTAIN] = Util::checkParameterRange("Envelope: SustainLevel", level, mSustainRange);
}

Util::ParameterRange<double> Envelope::mTimeRange = std::make_pair(0.0, 2000.0);
Util::ParameterRange<double> Envelope::mSustainRange = std::make_pair(0.0, 1.0);

}
