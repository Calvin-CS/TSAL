#include "Channel.h"

namespace tsal {
  
double Channel::getOutput() {
  return (mEffectChainEnd == nullptr) ? mChannelIn.getOutput() : mEffectChainEnd->getOutput();
}

/**
 * @brief Add an effect to the effect chain
 * 
 * @param effect 
 */
void Channel::add(Effect* effect) {
  effect->add(&mChannelIn);
  if (mEffectChainEnd == nullptr) {
  } else {
    // Remove the last effect and add it to the new one
    effect->add(mEffectChainEnd);
  }
  // Add the new effect as the last one in the chain
  mEffectChainEnd = effect;
}

/**
 * @brief Remove an effect from the effect chain 
 * 
 * @param effect 
 */
void Channel::remove(Effect* effect) {
  // If the effect is the last in the chain
  if (effect == mEffectChainEnd) {
    // Get the next effect in the chain
    mEffectChainEnd = effect->getNextEffect();
  } else {
    // The effect is not the last one, so pass up the chain
    mEffectChainEnd->remove(effect);
  } 
}

/**
 * @brief Add an instrument to the channel
 * 
* @param instrument 
 */
void Channel::add(Instrument* instrument) {
  mChannelIn.add((OutputDevice*) instrument);
}

/**
 * @brief Remove an instrument from the channel
 * 
 * @param instrument 
 */
void Channel::remove(Instrument* instrument) {
  mChannelIn.remove((OutputDevice*) instrument);
}

/**
 * @brief Route another channel through the current one
 * 
 * @param channel 
 */
void Channel::add(Channel* channel) {
  if (channel != this) {
    mChannelIn.add((OutputDevice*) channel);  
  }
}

/**
 * @brief Remove a routed channel
 * 
 * @param channel 
 */
void Channel::remove(Channel* channel) {
  mChannelIn.remove((OutputDevice*) channel);
}

};
