#include "LadspaEffect.hpp"
#include "LadspaManager.hpp"
#include <cmath>
#include <ladspa.h>

#define BUFFER_SIZE 2048
namespace tsal {

void LadspaEffect::loadPlugin(const std::string& pluginPath) {
  const LADSPA_Descriptor * descriptor;
  void * pluginHandle = dlopen(pluginPath.c_str(), RTLD_NOW);
  if (pluginHandle == NULL) {
    std::cout << "Failed to open plugin: " << pluginPath << std::endl;
    
  }
  
  LADSPA_Descriptor_Function descriptorFunction = (LADSPA_Descriptor_Function)dlsym(pluginHandle, "ladspa_descriptor");

  for (long pluginIndex = 0;; pluginIndex++) {
    descriptor = descriptorFunction(pluginIndex);
    if (descriptor == NULL) {
      std::cout << "Failed to initialize plugin " << pluginPath << std::endl;
      return;
    } else {
      std::cout << "Loading " << descriptor->Name << std::endl;
      mDescriptor = descriptor;
      break;
    }
  }
  mHandle = descriptor->instantiate(descriptor, mContext.getSampleRate());
  for (unsigned i = 0; i < descriptor->PortCount; i++) {
    auto portDescriptor = descriptor->PortDescriptors[i];
    if (LADSPA_IS_PORT_CONTROL(portDescriptor)) {
      LADSPA_PortRangeHintDescriptor hintDescriptor = mDescriptor->PortRangeHints[i].HintDescriptor;
      mControlPorts.push_back(0);
      descriptor->connect_port(mHandle, i, &mControlPorts[mControlPorts.size() - 1]);
      std::cout << "Port: " << descriptor->PortNames[i] << std::endl;
      if (LADSPA_IS_HINT_SAMPLE_RATE(hintDescriptor)) {
        std::cout << "\tSampleRate Dependent" << std::endl;
      }
      if (LADSPA_IS_HINT_BOUNDED_BELOW(hintDescriptor)) {
        std::cout << "\tBelow: " << mDescriptor->PortRangeHints[i].LowerBound << std::endl;
      }
      if (LADSPA_IS_HINT_BOUNDED_ABOVE(hintDescriptor)) {
        std::cout << "\tUpper: " << mDescriptor->PortRangeHints[i].UpperBound << std::endl;
      }
    }
    if (LADSPA_IS_PORT_AUDIO(portDescriptor)) {
      if (LADSPA_IS_PORT_INPUT(portDescriptor)) {
        mInputPorts.push_back(LadspaManager::Port(i));
      } 
      if (LADSPA_IS_PORT_OUTPUT(portDescriptor)) {
        mOutputPorts.push_back(LadspaManager::Port(i));
      } 
    }
  }

  if (descriptor->activate != NULL) {
    descriptor->activate(mHandle);
  }
  mControlPorts[0] = 0.0;
  mControlPorts[1] = 1.0;
}

void LadspaEffect::getOutput(AudioBuffer<float>& buffer) {
  std::vector<AudioBuffer<LADSPA_Data>*> inputBuffers;
  std::vector<AudioBuffer<LADSPA_Data>*> outputBuffers;
  for (auto& port : mInputPorts) {
    inputBuffers.push_back(&(port.buffer));
  }
  buffer.deinterleaveBuffer(inputBuffers);
  for (auto& port : mInputPorts) {
    mDescriptor->connect_port(mHandle, port.id, port.buffer.getRawPointer());
  }
  for (auto& port : mOutputPorts) {
    port.buffer.setSize(buffer.getFrameCount(), 1);
    mDescriptor->connect_port(mHandle, port.id, port.buffer.getRawPointer());
  }

  mDescriptor->run(mHandle, buffer.getFrameCount());

  for (auto& port : mOutputPorts) {
    outputBuffers.push_back(&(port.buffer));
  }
  buffer.interleaveBuffers(outputBuffers);
}

}
