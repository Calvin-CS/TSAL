#ifndef LADSPAEFFECT_H
#define LADSPAEFFECT_H

#include "Effect.hpp"
#include "AudioBuffer.hpp"
#include "LadspaManager.hpp"
#include <ladspa.h>

namespace tsal {

class LadspaEffect : public Effect {
  public:
    virtual void getOutput(AudioBuffer<float>& buffer) override;
    void loadPlugin(const std::string& pluginPath);
  private:
    LADSPA_Handle mHandle;
    const LADSPA_Descriptor * mDescriptor;
    std::vector<LadspaManager::Port> mInputPorts;
    std::vector<LadspaManager::Port> mOutputPorts;
    std::vector<LADSPA_Data> mControlPorts;
};

}

#endif
