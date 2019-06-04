#include "InputDevice.h"

namespace tsal {

double InputDevice::getInput() {
  double input = 0.0;
  for (auto device : mOutputDevices) {
    input += device->getOutput();
  }
  return input;
}

void InputDevice::add(OutputDevice* output) {
  mOutputDevices.push_back(output);
}

}
