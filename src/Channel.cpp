#include "Channel.h"

namespace tsal {
  
double Channel::getOutput() {
  return mEffectChain->getOutput();
}

void Channel::add(Effect* effect) {
  if (mEffectChain == nullptr) {
    mEffectChain = effect;
    effect->InputDevice::add(this);
  } else {
    effect->add(mEffectChain);
    mEffectChain = effect;
  } 
}

};
