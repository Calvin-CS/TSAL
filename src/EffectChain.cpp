#include "EffectChain.hpp"

namespace tsal {

EffectChain::~EffectChain() {
  lock();
  for (unsigned i = 0; i < mEffects.size(); i++) {
    remove(*mEffects[i]);
  }
}

double EffectChain::getOutput() {
  return (mEffects.size() == 0) ? mInput.getOutput() : mEffects.back()->getOutput();
}

void EffectChain::getOutput(AudioBuffer<float> &buffer) {
  // if (mEffects.size() == 0) {
  //   mInput.getOutput(buffer);
  // } else {
  //   mEffects.back()->getOutput(buffer);
  // }
  for (auto effect : mEffects) {
    effect->getOutput(buffer);
  }
}

void EffectChain::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  lock();
  for (auto effect : mEffects) {
    effect->setMixer(mixer);
  }
} 

/* @brief Add an effect to the end of the chain
 *
 * @param effect
 */
void EffectChain::add(Effect& effect) {
  lock();
  effect.setMixer(mMixer);
  mEffects.push_back(&effect);
}

/* @brief Remove an effect from the effect chain
 *
 * @param effect
 */
void EffectChain::remove(Effect& effect) {
  lock();
  for (unsigned i = 1; i < mEffects.size() - 1; i++) {
    if (mEffects[i] == &effect) {
      mEffects.erase(mEffects.begin() + i);
    }
  }
}

}
