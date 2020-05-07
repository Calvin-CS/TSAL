#include "OutputDevice.hpp"
#include "Util.hpp"
#include <cmath>

namespace tsal {

/**
 * @brief Set the active status of the device
 * 
 * It is up to the class how to implement the active status
 * 
 * @param active o
 */
void OutputDevice::setActive(bool active) { 
  mActive = active; 
}

/**
 * @brief Check if the device is active
 *
 * @return bool
 */
bool OutputDevice::isActive() const {
  return mActive;
}

// Util::ParameterRange<double> OutputDevice::mGainRange = std::make_pair(-50.0, 50.0);
// Util::ParameterRange<double> OutputDevice::mVolumeRange = std::make_pair(0.0, 2.0);

}
