#include "InputDevice.h"
#include <algorithm>

namespace tsal {

/**
 * @brief Get the input from the attached output devices 
 * 
 * @return double 
 */
double InputDevice::getInput() {
  double output = 0.0;
  for (auto device : mOutputDevices) {
    output += device->getOutput();
  }
  return output;
}

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
void InputDevice::add(OutputDevice* output) {
  mOutputDevices.push_back(output);
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
void InputDevice::remove(OutputDevice *output) {
  mOutputDevices.erase(
      std::remove(mOutputDevices.begin(), mOutputDevices.end(), output));
}

};
