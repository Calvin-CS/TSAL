#include "LadspaEffect.hpp"
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
  mHandle = descriptor->instantiate(descriptor, 100);
  for (unsigned i = 0; i < descriptor->PortCount; i++) {
    auto portDescriptor = descriptor->PortDescriptors[i];
    if (LADSPA_IS_PORT_CONTROL(portDescriptor)) {
      std::cout << "Port: " << descriptor->PortNames[i] << std::endl;
    }
    if (LADSPA_IS_PORT_AUDIO(portDescriptor)) {
      if (LADSPA_IS_PORT_INPUT(portDescriptor)) {
        std::cout << "Port Input: " << descriptor->PortNames[i] << std::endl;
        LADSPA_Data *buf = (LADSPA_Data *)calloc(BUFFER_SIZE, sizeof(LADSPA_Data));
        mBuffersTest.push_back(buf);
        descriptor->connect_port(mHandle, i, buf);
        // mBuffers.push_back(std::make_unique<AudioBuffer<float>>(1, 1));
        // std::cout << "Hi" << mBuffers[mBuffers.size() - 1]->getChannelCount() << std::endl;
        // std::cout << "Connecting to buffer: " << mBuffers.size() << " " << mBuffers[mBuffers.size() - 1]->getRawPointer() << std::endl;
        // descriptor->connect_port(mHandle, i, mBuffers[mBuffers.size() - 1]->getRawPointer());

      } 
      if (LADSPA_IS_PORT_OUTPUT(portDescriptor)) {
        LADSPA_Data *buf = (LADSPA_Data *)calloc(BUFFER_SIZE, sizeof(LADSPA_Data));
        mBuffersTest.push_back(buf);
        descriptor->connect_port(mHandle, i, buf);
        // std::cout << "Port Output: " << descriptor->PortNames[i] << std::endl;
        // mBuffers.push_back(std::make_unique<AudioBuffer<float>>(1, 1));
        // std::cout << "Connecting to buffer: " << mBuffers[mBuffers.size() - 1]->getRawPointer() << std::endl;
        // descriptor->connect_port(mHandle, i, mBuffers[mBuffers.size() - 1]->getRawPointer());
      } 
    }
    if (LADSPA_IS_PORT_CONTROL(portDescriptor)) {
      mControls.push_back(1);
      descriptor->connect_port(mHandle, i, &mControls[mControls.size() - 1]);
    }
  }

  // descriptor->activate(plugin);
  if (descriptor->activate != NULL) {
    descriptor->activate(mHandle);
  }
  mControls[0] = 0.5;
}

void LadspaEffect::getOutput(AudioBuffer<float>& buffer) {
  // mBuffers[0]->copyBuffer(buffer);
  // mBuffers[1]->copyBuffer(buffer);
  for (unsigned i = 0; i < buffer.size(); i++) {
    mBuffersTest[0][i] = buffer[i];
  }

  mDescriptor->run(mHandle, BUFFER_SIZE);
  for (unsigned i = 0; i < buffer.size(); i++) {
    buffer[i] = mBuffersTest[1][i];
  }
  // buffer.copyBuffer(*mBuffers[1]);
}

}
