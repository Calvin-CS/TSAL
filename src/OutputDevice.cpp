#include "OutputDevice.hpp"
#include "Mixer.hpp"

namespace tsal {
/**
 * @brief Get the output for the device
 * 
 * @return double 
 */
double OutputDevice::getOutput() { 
  return 0.0; 
}

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
 * @brief Set the gain
 * 
 * @param gain 
 */
void OutputDevice::setGain(double gain) {
  mAmp = Util::dbToAmp(Util::checkParameterRange("Oscillator: Gain", gain, mGainRange));
}

/**
 * @brief Get the gain
 * 
 * @return double 
 */
double OutputDevice::getGain() const {
  return Util::ampToDb(mAmp);
}

void OutputDevice::setVolume(double volume) {
  mAmp = Util::dbToAmp(Util::volumeToDb(volume));
}

double OutputDevice::getVolume() const {
  return Util::dbToVolume(getGain());
}

bool OutputDevice::isActive() const {
  return mActive;
}

Mixer* OutputDevice::getMixer() {
  if (mMixer == nullptr) {
    std::cout << "OutputDevice: Mixer not set" << std::endl;
  }
  return mMixer;
}

Util::ParameterRange<double> OutputDevice::mGainRange = std::make_pair(-50.0, 50.0);
Util::ParameterRange<double> OutputDevice::mVolumeRange = std::make_pair(0.0, 2.0);

}
