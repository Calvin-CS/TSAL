#include "InputDevice.h"
#include <algorithm>

namespace tsal {

double InputDevice::getInput() {
  double output = 0.0;
  for (auto device : mOutputDevices) {
    output += device->getOutput();
  }
  return output;
}

void InputDevice::add(OutputDevice* output) {
  mOutputDevices.push_back(output);
}

void InputDevice::remove(OutputDevice *output) {
  mOutputDevices.erase(
      std::remove(mOutputDevices.begin(), mOutputDevices.end(), output));
}

};
