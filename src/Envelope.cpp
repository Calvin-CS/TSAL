#include "Envelope.hpp"

namespace tsal {

template <typename Item>
Item checkParameterRangeWithMax(const std::string& name, Item value, std::pair<Item, Item> range) {
  return std::max(checkParameterRange(name, value, range), MIN_VALUE);
}

Envelope::Envelope() {
  mStateValue[OFF] = MIN_VALUE;
  mStateValue[ATTACK] = 0.001;
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

/**
 * @brief Gets the current sample of the envelope
 * 
 * @return double A sample of the envelope
 */
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

/**
 * @brief Calculate the multiplier that will be used to update the envelope value
 * 
 * Human sense are logarithmic, the envelope needs to change exponentially
 * This function calculates an appropriate multiplier that gets the envelope value 
 * from a start level to an end level in the number of specified samples (time)
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
  mStateValue[SUSTAIN] = checkParameterRange("Envelope: SustainLevel", level, mSustainRange);
}

ParameterRange<double> Envelope::mTimeRange = std::make_pair(0.0, 2000.0);
ParameterRange<double> Envelope::mSustainRange = std::make_pair(0.0, 1.0);

}
