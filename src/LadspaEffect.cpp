#include "LadspaEffect.hpp"
#include "LadspaManager.hpp"
#include <cmath>
#include <ladspa.h>

namespace tsal {

void LadspaEffect::loadPlugin(const std::string& pluginPath) {
  mDescriptor = LadspaManager::loadPlugin(pluginPath);
  
  mHandle = mDescriptor->instantiate(mDescriptor, mContext.getSampleRate());
  for (unsigned i = 0; i < mDescriptor->PortCount; i++) {
    auto portDescriptor = mDescriptor->PortDescriptors[i];
    if (LADSPA_IS_PORT_CONTROL(portDescriptor)) {
      LADSPA_PortRangeHintDescriptor hintDescriptor = mDescriptor->PortRangeHints[i].HintDescriptor;
      mControlPorts.push_back(0);
      mDescriptor->connect_port(mHandle, i, &mControlPorts[mControlPorts.size() - 1]);
      std::cout << "Port: " << mDescriptor->PortNames[i] << std::endl;
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

  if (mDescriptor->activate != NULL) {
    mDescriptor->activate(mHandle);
  }
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
