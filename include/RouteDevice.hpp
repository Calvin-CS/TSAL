#ifndef ROUTEDEVICE_H
#define ROUTEDEVICE_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"
#include <mutex>

namespace tsal {

/** @class RouteDevice
 * @brief Routes any number of inputs into a single output
 *
 * RouteDevice is a flexible class intended to make managing inputs easier.
 * Combining multiple inputs is as simple as adding up all the input values.
 */
template <typename DeviceType>
class RouteDevice : public InputDevice, public OutputDevice {
  public:
    RouteDevice(Mixer* mixer) : OutputDevice(mixer){};
    ~RouteDevice();
    virtual double getInput() override;
    virtual double getOutput() override;
    virtual void setMixer(Mixer* mixer) override;
    
    void add(DeviceType& output);
    void remove(DeviceType& output);
    int size() { return mInputDevices.size(); };
    
    DeviceType& operator[](const int index);
    const DeviceType& operator[](const int index) const;
    
    std::vector<DeviceType*>& getInputDevices() { return mInputDevices; };

  protected:
    bool outOfRange(const int index) const;
    std::vector<DeviceType*> mInputDevices;
    std::mutex mVectorMutex;
};

template <typename DeviceType>
RouteDevice<DeviceType>::~RouteDevice() {
  std::lock_guard<std::mutex> guard(mVectorMutex);
  for (unsigned i = 0; i < mInputDevices.size(); i++) {
    mInputDevices.erase(mInputDevices.begin() + i);
  }
}

/**
 * @brief Get the input from the attached output devices 
 * 
 * @return double 
 */
template <typename DeviceType>
double RouteDevice<DeviceType>::getInput() {
  double output = 0.0;
  std::lock_guard<std::mutex> guard(mVectorMutex); 
  for (auto d : mInputDevices) {
    output += d->getOutput();
  }
  return output;
}

template <typename DeviceType>
double RouteDevice<DeviceType>::getOutput() {
  return getInput();
}

template <typename DeviceType>
void RouteDevice<DeviceType>::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  for (auto d : mInputDevices) {
    d->setMixer(mixer);
  }
}
  

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::add(DeviceType& output) {
  std::lock_guard<std::mutex> guard(mVectorMutex); 
  output.setMixer(mMixer);
  mInputDevices.push_back(&output);
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::remove(DeviceType& output) {
  std::lock_guard<std::mutex> guard(mVectorMutex);
  for (unsigned i = 0; i < mInputDevices.size(); i++) {
    if (&output == mInputDevices[i]) {
      mInputDevices.erase(mInputDevices.begin() + i);
      break;
    }
  }
}

template <typename DeviceType>
DeviceType& RouteDevice<DeviceType>::operator[](const int index) {
  if (outOfRange(index)) {
    throw "RouteDevice: Index out of range";
  }
  return *mInputDevices[index];
}

template <typename DeviceType>
const DeviceType& RouteDevice<DeviceType>::operator[](const int index) const {
  if (outOfRange(index)) {
    throw "RouteDevice: Index out of range";
  }
  return *mInputDevices[index];
}

template <typename DeviceType>
bool RouteDevice<DeviceType>::outOfRange(const int index) const {
  return index < 0 || index > (int) mInputDevices.size();
}
    
} // namespace tsal
#endif
