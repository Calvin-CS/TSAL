#ifndef ROUTEDEVICE_H
#define ROUTEDEVICE_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"
#include <mutex>
#include <vector>

namespace tsal {

/** @class RouteDevice
 * @brief Routes any number of inputs into a single output
 *
 * RouteDevice is a flexible class intended to make managing inputs easier.
 * Combining multiple inputs is as simple as adding up all the input values.
 */
template <typename DeviceType>
class RouteDevice : public OutputDevice {
  public:
    RouteDevice(Mixer* mixer) : OutputDevice(mixer){};
    ~RouteDevice();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    virtual void setMixer(Mixer* mixer) override;
    
    void add(DeviceType& device);
    void remove(DeviceType& device);
    int size() { return mRoutedInputs.size(); };
    DeviceType& operator[](const int index);
    const DeviceType& operator[](const int index) const;
    
    // std::vector<DeviceType*>& getInputDevices() { return mRoutedInputs; };

  protected:
    /* Store an input device with an output buffer
     * Each device buffer is combined/mixed within this class
     * so that they aren't modifying existing data
     */ 
    struct RoutedInput {
        DeviceType* device;
        AudioBuffer<float> buffer;
        RoutedInput(DeviceType* d, Mixer* mixer)
          : device(d) {};
    };
    bool outOfRange(const int index) const;
    std::vector<RoutedInput*> mRoutedInputs;
};


template <typename DeviceType>
RouteDevice<DeviceType>::~RouteDevice() {
  for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
    mRoutedInputs.erase(mRoutedInputs.begin() + i);
  }
}

template <typename DeviceType>
void RouteDevice<DeviceType>::getOutput(AudioBuffer<float> &buffer) {
  for (auto routedInput : mRoutedInputs) {
    routedInput->buffer.setSize(buffer);
    routedInput->device->getOutput(routedInput->buffer);
    for (unsigned i = 0; i < buffer.size(); i++) {
      buffer[i] += routedInput->buffer[i];
    }
  }
};

template <typename DeviceType>
void RouteDevice<DeviceType>::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
    mRoutedInputs[i]->device->setMixer(mixer);
  }
}

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::add(DeviceType& device) {
  device.setMixer(mMixer);
  mRoutedInputs.push_back(new RoutedInput(&device, mMixer));
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::remove(DeviceType& device) {
  for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
    if (&device == mRoutedInputs[i]->device) {
      mRoutedInputs.erase(mRoutedInputs.begin() + i);
      break;
    }
  }
}

template <typename DeviceType>
DeviceType& RouteDevice<DeviceType>::operator[](const int index) {
  if (outOfRange(index)) {
    throw "RouteDevice: Index out of range";
  }
  return *(mRoutedInputs[index]->device);
}

template <typename DeviceType>
const DeviceType& RouteDevice<DeviceType>::operator[](const int index) const {
  if (outOfRange(index)) {
    throw "RouteDevice: Index out of range";
  }
  return *(mRoutedInputs[index]->device);
}

template <typename DeviceType>
bool RouteDevice<DeviceType>::outOfRange(const int index) const {
  return index < 0 || index > (int) mRoutedInputs.size();
}
    
} // namespace tsal
#endif
