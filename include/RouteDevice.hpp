#ifndef ROUTEDEVICE_H
#define ROUTEDEVICE_H

#include "OutputDevice.hpp"
#include <mutex>
#include <vector>
#include <memory>
#include <functional>

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
    RouteDevice() {};
    ~RouteDevice();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    virtual void updateContext(const Context& context) override;
    
    void add(DeviceType& device);
    void remove(DeviceType& device);
    int size() { return mRoutedInputs.size(); };
    DeviceType& operator[](const int index);
    const DeviceType& operator[](const int index) const;
    
    // std::vector<DeviceType*>& getInputDevices() { return mRoutedInputs; };

  protected:
    void addDeviceToModel(DeviceType& device);
    void removeDeviceFromModel(DeviceType& device);
    /* Store an input device with an output buffer
     * Each device buffer is combined/mixed within this class
     * so that they aren't modifying existing data
     */ 
    struct RoutedInput {
        RoutedInput(DeviceType* d)
          : device(d) {};
        DeviceType* device;
        AudioBuffer<float> buffer;
    };
    bool outOfRange(const int index) const;
    std::vector<std::unique_ptr<RoutedInput>> mRoutedInputs;
};


template <typename DeviceType>
RouteDevice<DeviceType>::~RouteDevice() {
  for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
    mRoutedInputs.erase(mRoutedInputs.begin() + i);
  }
}

template <typename DeviceType>
void RouteDevice<DeviceType>::getOutput(AudioBuffer<float> &buffer) {
  for (const auto& routedInput : mRoutedInputs) {
    routedInput->buffer.setSize(buffer);
    routedInput->buffer.clear();
    routedInput->device->getOutput(routedInput->buffer);
    for (unsigned i = 0; i < buffer.size(); i++) {
      buffer[i] += routedInput->buffer[i];
    }
  }
};

template <typename DeviceType>
void RouteDevice<DeviceType>::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  for (const auto& routedInput : mRoutedInputs) {
    routedInput->device->updateContext(context);
  }
}

/**
 * @brief Add an output device as input
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::add(DeviceType& device) {
  mContext.requestModelChange(std::bind(&RouteDevice<DeviceType>::addDeviceToModel, this, std::ref(device)));
}

template <typename DeviceType>
void RouteDevice<DeviceType>::addDeviceToModel(DeviceType& device) {
  device.updateContext(mContext);
  mRoutedInputs.push_back(std::make_unique<RoutedInput>(&device));
}

/**
 * @brief Remove an output device
 * 
 * @param output 
 */
template <typename DeviceType>
void RouteDevice<DeviceType>::remove(DeviceType& device) {
  mContext.requestModelChange(std::bind(&RouteDevice<DeviceType>::removeDeviceFromModel, this, std::ref(device)));
}

template <typename DeviceType>
void RouteDevice<DeviceType>::removeDeviceFromModel(DeviceType& device) {
  for (unsigned i = 0; i < mRoutedInputs.size(); i++) {
    if (&device == mRoutedInputs[i]->device) {
      device.updateContext(Context::clear());
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
