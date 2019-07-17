#include "EffectChain.hpp"

namespace tsal {
  
void EffectChain::setInput(OutputDevice& input) {
  mInput = &input;
}

double EffectChain::getOutput() {
  return (mEffects.size() == 0) ? mInput->getOutput() : mEffects.back()->getOutput();
}

void EffectChain::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  for (auto effect : mEffects) {
    effect->setMixer(mixer);
  }
} 

void EffectChain::add(Effect& effect) {
   effect.setMixer(mMixer);
  if (mEffects.size() == 0) {
    effect.setInput(mInput);
    mEffects.push_back(&effect);
  } else {
    effect.setInput(mEffects.back());
    mEffects.push_back(&effect);
  }
}

void EffectChain::remove(Effect& effect) {
  if (mEffects.size() == 0) {
    return;
  }

  const auto effectPtr = &effect;

  if (mEffects.front() == effectPtr) {
    // Front case
    mEffects.erase(mEffects.begin());
    if (mEffects.size() > 0) {
      mEffects.front()->setInput(mInput);
    }
  } else if (mEffects.back() == effectPtr) {
    // Back case
    mEffects.pop_back();
  } else {
    // Middle case
    for (unsigned i = 1; i < mEffects.size() - 1; i++) {
      if (mEffects[i] == &effect) {
        mEffects[i + 1]->setInput(mEffects[i - 1]);
        mEffects.erase(mEffects.begin() + i);
      }
    }
  }
}

}
