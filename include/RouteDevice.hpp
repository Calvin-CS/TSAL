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
    virtual void getOutput(std::vector<float>& buffer, unsigned long frameCount, unsigned channelCount) override;
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
        std::vector<float> buffer;
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
void RouteDevice<DeviceType>::getOutput(std::vector<float> &buffer, unsigned long frameCount,
                                       unsigned channelCount) {
  // for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
  //   std::cout << "
  // }
  for (auto routedInput : mRoutedInputs) {
    if (routedInput->buffer.size() < frameCount * channelCount) {
      // std::cout << "Updating buffer size: " + routedInput->buffer.size() << " to " <<
      //           frameCount * channelCount << std::endl;
      // routedInput->buffer.resize(frameCount * channelCount);
    }
    routedInput->device->getOutput(routedInput->buffer, frameCount, channelCount);
    for (unsigned i = 0; i < routedInput->buffer.size(); i++) {
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
  printf("Connecting to device: %p\n", (void*)&device);
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
