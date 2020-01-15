#include "EffectChain.hpp"

namespace tsal {

EffectChain::~EffectChain() {
  for (unsigned i = 0; i < mEffects.size(); i++) {
    remove(*mEffects[i]);
  }
}

void EffectChain::getOutput(AudioBuffer<float> &buffer) {
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
  for (auto effect : mEffects) {
    effect->getOutput(buffer);
  }
}

void EffectChain::updateContext(const Context& context) {
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
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
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
  effect.updateContext(mContext);
  mEffects.push_back(&effect);
}

/* @brief Remove an effect from the effect chain
 *
 * @param effect
 */
void EffectChain::remove(Effect& effect) {
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
  for (unsigned i = 1; i < mEffects.size() - 1; i++) {
    if (mEffects[i] == &effect) {
      mEffects.erase(mEffects.begin() + i);
    }
  }
}

}
