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

}
