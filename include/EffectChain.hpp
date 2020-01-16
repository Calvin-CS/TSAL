#ifndef EFFECTCHAIN_H
#define EFFECTCHAIN_H

#include "OutputDevice.hpp"
#include "Effect.hpp"
#include <functional>

namespace tsal {

/** @class EffectChain
 * @brief Manages the effect chain for a channel
 *
 * Effects are applied to a channel linked in a chain and updating the audio 
 * stream as it passes through the chain
 */
class EffectChain : public OutputDevice {
  public:
    EffectChain() {};
    EffectChain(const Context& context) : OutputDevice(context) {};
    ~EffectChain();
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    virtual void updateContext(const Context& context) override;
    void add(Effect& effect);
    void remove(Effect& effect);
    int size() { return mEffects.size(); };
  private:
    std::vector<Effect*> mEffects;
    void addDeviceToModel(Effect& effect);
    void removeDeviceFromModel(Effect& effect);
};

}

#endif
