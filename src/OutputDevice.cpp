#include "OutputDevice.hpp"
#include "Util.hpp"
#include <cmath>

namespace tsal {

/**
 * @brief Set the active status of the device
 * 
 * It is up to the class how to implement the active status
 * 
 * @param active 
 */
void OutputDevice::setActive(bool active) { 
  mActive = active; 
}


/**
 * @brief Set the panning modifier or all the channels
 * 
 * @param gain 
 */
void OutputDevice::setChannelPanning(unsigned channelCount) {
  switch (channelCount) {
    // mono channel
    case 1: {
      const double delta = (mPanning + 1)/2.0;
      mChannelPanning.resize(1);
      mChannelPanning[0] = delta;
      break;
    }
    // stereo channel
    case 2: {
      const double delta = (mPanning + 1) * M_PI/4.0;
      mChannelPanning.resize(2);
      mChannelPanning[0] = cos(delta);
      mChannelPanning[1] = sin(delta);
      break;
    }
  }
}

void OutputDevice::setPanning(double panning) {
  mPanning = Util::checkParameterRange("Oscillator: Panning", panning, mPanningRange);
}

/**
 * @brief Set the amplitude modifer from a db value
 * 
 * @param gain 
 */
void OutputDevice::setGain(double gain) {
  mAmp = Util::dbToAmp(Util::checkParameterRange("Oscillator: Gain", gain, mGainRange));
}

/**
 * @brief Get the amplitude modifier in db
 * 
 * @return double 
 */
double OutputDevice::getGain() const {
  return Util::ampToDb(mAmp);
}

/**
 * @brief Set the amplitude modifer from a volume
 * 
 * @return double 
 */
void OutputDevice::setVolume(double volume) {
  mAmp = Util::dbToAmp(Util::volumeToDb(Util::checkParameterRange("Oscillator: Volume", volume, mVolumeRange)));
}

/**
 * @brief Get the amplitude modifier in volume
 * 
 * @return double 
 */
double OutputDevice::getVolume() const {
  return Util::dbToVolume(getGain());
}

/**
 * @brief Check if the device is active
 *
 * @return bool
 */
bool OutputDevice::isActive() const {
  return mActive;
}

Util::ParameterRange<double> OutputDevice::mGainRange = std::make_pair(-50.0, 50.0);
Util::ParameterRange<double> OutputDevice::mVolumeRange = std::make_pair(0.0, 2.0);
Util::ParameterRange<double> OutputDevice::mPanningRange = std::make_pair(-1.0, 1.0);

}
