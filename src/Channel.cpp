#include "Channel.h"

namespace tsal {
  
Channel::Channel() {
  InputDevice::add(&mChannelIn);
}

void Channel::add(Effect* effect) {
  effect->add(&mChannelIn);
  if (mEffectChain == nullptr) {
    // Remove the ChannelIn since we currently have no effects
    InputDevice::remove(&mChannelIn);
  } else {
    // Remove the first effect and add it to the new one
    InputDevice::remove(mEffectChain);
    effect->add(mEffectChain);
  }
  // Add the new effect as the first one in the chain
  mEffectChain = effect;
  InputDevice::add(mEffectChain);
}

void Channel::remove(Effect* effect) {
  // If the effect is the first in the chain
  if (effect == mEffectChain) {
    // Get the next effect in the chain
    Effect* nextEffect = effect->getNextEffect();
    // Remove the current effect from the input
    InputDevice::remove(effect);
    if (nextEffect == nullptr) {
      // If this is the last effect, reattach the ChannelIn
      InputDevice::add(&mChannelIn);
    } else {
      // Attach the next effect as the first effect in the chain
      mEffectChain = effect;
      InputDevice::add(nextEffect);
    }
  } else {
    // The effect is not the first one, so pass along to the chain
    mEffectChain->remove(effect);
  } 
}

void Channel::add(Instrument* instrument) {
  mChannelIn.add(instrument);
}

void Channel::remove(Instrument* instrument) {
  mChannelIn.remove(instrument);
}

void Channel::add(Channel* channel) {
  mChannelIn.add(channel);
}

void Channel::remove(Channel* channel) {
  mChannelIn.remove(channel);
}

};
