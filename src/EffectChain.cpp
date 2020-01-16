#include "EffectChain.hpp"

namespace tsal {

EffectChain::~EffectChain() {
  for (unsigned i = 0; i < mEffects.size(); i++) {
    remove(*mEffects[i]);
  }
}

void EffectChain::getOutput(AudioBuffer<float> &buffer) {
  for (auto effect : mEffects) {
    effect->getOutput(buffer);
  }
}

void EffectChain::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  for (auto effect : mEffects) {
    effect->updateContext(context);
  }
} 

/* @brief Add an effect to the end of the chain
 *
 * @param effect
 */
void EffectChain::add(Effect& effect) {
  mContext.requestModelChange(std::bind(&EffectChain::addDeviceToModel, this, std::ref(effect)));
}

void EffectChain::addDeviceToModel(Effect& effect) {
  effect.updateContext(mContext);
  mEffects.push_back(&effect);
}

/* @brief Remove an effect from the effect chain
 *
 * @param effect
 */
void EffectChain::remove(Effect& effect) {
  mContext.requestModelChange(std::bind(&EffectChain::removeDeviceFromModel, this, std::ref(effect)));
}

void EffectChain::removeDeviceFromModel(Effect& effect) {
  for (unsigned i = 1; i < mEffects.size() - 1; i++) {
    if (mEffects[i] == &effect) {
      effect.updateContext(Context::clear());
      mEffects.erase(mEffects.begin() + i);
    }
  }
}

}
