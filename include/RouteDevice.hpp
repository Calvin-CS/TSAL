#ifndef ROUTEDEVICE_H
#define ROUTEDEVICE_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"

namespace tsal {

template <typename DeviceType>
class RouteDevice : public InputDevice, public OutputDevice {
  public:
    virtual double getInput() override;
    virtual double getOutput() override;
    void add(DeviceType& output);
    void remove(DeviceType& output);
    DeviceType& operator[](const int index);
    const DeviceType& operator[](const int index) const;
    std::vector<DeviceType*>& getInputDevices() { return mInputDevices; };

  protected:
    std::vector<DeviceType*> mInputDevices;
};

/**
 * @brief Get the input from the attached output devices 
 * 
 * @return double 
 */
template <typename DeviceType>
double RouteDevice<DeviceType>::getInput() {
  double output = 0.0;
  for (auto d : mInputDevices) {
    output += d->getOutput();
  }
  return output;
}

template <typename DeviceType>
double RouteDevice<DeviceType>::getOutput() {
  return getInput();
}

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::add(DeviceType& output) {
  mInputDevices.push_back(&output);
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::remove(DeviceType& output) {
  for (auto it = mInputDevices.begin(); it != mInputDevices.end(); it++) {
    if (&output == (*it)) {
      mInputDevices.erase(it);
      //std::cout << "Removing device" << std::endl;  
      break;
    }
  }
}

template <typename DeviceType>
DeviceType& RouteDevice<DeviceType>::operator[](const int index) {
  return *mInputDevices[index];
}

template <typename DeviceType>
const DeviceType& RouteDevice<DeviceType>::operator[](const int index) const {
  return *mInputDevices[index];
}

} // namespace tsal
#endif
