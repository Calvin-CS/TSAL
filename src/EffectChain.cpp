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

void EffectChain::setMixer(Mixer* mixer) {
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
  OutputDevice::setMixer(mixer);
  for (auto effect : mEffects) {
    effect->setMixer(mixer);
  }
} 

/* @brief Add an effect to the end of the chain
 *
 * @param effect
 */
void EffectChain::add(Effect& effect) {
  std::lock_guard<std::mutex> guard(mEffectChainMutex);
  effect.setMixer(mMixer);
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
