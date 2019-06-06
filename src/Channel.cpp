#include "Channel.h"

namespace tsal {
  
/**
 * @brief Construct a new Channel
 * 
 */
Channel::Channel() {
  InputDevice::add(&mChannelIn);
}

/**
 * @brief Add an effect to the effect chain
 * 
 * @param effect 
 */
void Channel::add(Effect* effect) {
  effect->add(&mChannelIn);
  if (mEffectChainEnd == nullptr) {
    // Remove the ChannelIn since we currently have no effects
    InputDevice::remove(&mChannelIn);
  } else {
    // Remove the last effect and add it to the new one
    InputDevice::remove(mEffectChainEnd);
    effect->add(mEffectChainEnd);
  }
  // Add the new effect as the last one in the chain
  mEffectChainEnd = effect;
  InputDevice::add(mEffectChainEnd);
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
    Effect* nextEffect = effect->getNextEffect();
    // Remove the current effect from the input
    InputDevice::remove(effect);
    if (nextEffect == nullptr) {
      // If this is the last effect, reattach the ChannelIn
      InputDevice::add(&mChannelIn);
    } else {
      // Attach the next effect as the last effect in the chain
      mEffectChainEnd = effect;
      InputDevice::add(nextEffect);
    }
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
  mChannelIn.add(instrument);
}

/**
 * @brief Remove an instrument from the channel
 * 
 * @param instrument 
 */
void Channel::remove(Instrument* instrument) {
  mChannelIn.remove(instrument);
}

/**
 * @brief Route another channel through the current one
 * 
 * @param channel 
 */
void Channel::add(Channel* channel) {
  if (channel != this) {
    mChannelIn.add(channel);  
  }
}

/**
 * @brief Remove a routed channel
 * 
 * @param channel 
 */
void Channel::remove(Channel* channel) {
  mChannelIn.remove(channel);
}

};
