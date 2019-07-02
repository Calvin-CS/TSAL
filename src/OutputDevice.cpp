#include "OutputDevice.hpp"

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
  mAmp = dbToAmp(checkParameterRange("Oscillator: Gain", gain, mGainRange));
}

/**
 * @brief Get the gain
 * 
 * @return double 
 */
double OutputDevice::getGain() const {
  return ampToDb(mAmp);
}

void OutputDevice::setVolume(double volume) {
  mAmp = dbToAmp(volumeToDb(volume));
}

double OutputDevice::getVolume() const {
  return dbToVolume(getGain());
}

ParameterRange<double> OutputDevice::mGainRange = std::make_pair(-50.0, 50.0);
ParameterRange<double> OutputDevice::mVolumeRange = std::make_pair(0.0, 2.0);

}
