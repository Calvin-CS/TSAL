#include "Channel.h"

namespace tsal {
  
double Channel::getOutput() {
  return (mEffectChain == nullptr) ? mChannelIn.getOutput() : mEffectChain->getOutput();
}

void Channel::add(Effect* effect) {
  if (mEffectChain == nullptr) {
    mEffectChain = effect;
    effect->InputDevice::add(&mChannelIn);
  } else {
    effect->add(mEffectChain);
    mEffectChain = effect;
  } 
}

void Channel::add(Instrument* instrument) {
  mChannelIn.add(instrument);
}

};
