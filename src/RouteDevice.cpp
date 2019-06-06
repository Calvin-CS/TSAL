#include "RouteDevice.h"
#include <algorithm>

namespace tsal {

/**
 * @brief Get the input from the attached output devices 
 * 
 * @return double 
 */
double RouteDevice::getInput() {
  double output = 0.0;
  for (auto d : mOutputDevices) {
    output += d->getOutput();
  }
  return output;
}

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
void RouteDevice::add(OutputDevice* output) {
  mOutputDevices.push_back(output);
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
void RouteDevice::remove(OutputDevice* output) {
  mOutputDevices.erase(std::remove(mOutputDevices.begin(), mOutputDevices.end(), output));
}

};
