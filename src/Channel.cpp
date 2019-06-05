#include "Channel.h"

namespace tsal {
  
Channel::Channel() {
  InputDevice::add(&mChannelIn);
}

void Channel::add(Effect* effect) {
  if (mEffectChain == nullptr) {
    InputDevice::remove(&mChannelIn);
    effect->add(&mChannelIn);
  } else {
    InputDevice::remove(mEffectChain);
    effect->add(mEffectChain);
  }
  mEffectChain = effect;
  InputDevice::add(mEffectChain);
}

void Channel::add(Instrument* instrument) {
  mChannelIn.add(instrument);
}

void Channel::remove(Instrument* instrument) {
  mChannelIn.remove(instrument);
}

};
