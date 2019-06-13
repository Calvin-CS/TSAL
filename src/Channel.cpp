#include "Channel.h"

namespace tsal {
  
Channel::Channel() {
  mChannelIn.add(mRoutedInstruments);
  mChannelIn.add(mRoutedChannels);
}

double Channel::getOutput() {
  return (mEffectChainEnd == nullptr) ? mChannelIn.getOutput() : mEffectChainEnd->getOutput();
}

/**
 * @brief Add an effect to the end of the effect chain
 * 
 * @param effect 
 */
void Channel::add(Effect& effect) {
  Effect* effectPtr = &effect;
  effectPtr->setChannel(&mChannelIn);
  if (mEffectChainEnd != nullptr) {
    // Set the last effect to be the second to last effect
    effectPtr->setNextEffect(mEffectChainEnd);
  }
  // Add the new effect as the last one in the chain
  mEffectChainEnd = effectPtr;
}
/**
 * @brief Remove an effect from the effect chain 
 * 
 * @param effect 
 */
void Channel::remove(Effect& effect) {
  Effect* effectPtr = &effect;
  // If the effect is the last in the chain
  if (effectPtr == mEffectChainEnd) {
    // Get the next effect in the chain and set it as the end effect
    mEffectChainEnd = effectPtr->getNextEffect();
    effectPtr->clear();
  } else {
    // The effect is not the last one, so pass up the chain
    mEffectChainEnd->remove(effectPtr);
  } 
}

/**
 * @brief Add an instrument to the channel
 * 
* @param instrument 
 */
void Channel::add(Instrument& instrument) {
  mRoutedInstruments.add(instrument);
}

/**
 * @brief Remove an instrument from the channel
 * 
 * @param instrument 
 */
void Channel::remove(Instrument& instrument) {
  mRoutedInstruments.remove(instrument);
}

/**
 * @brief Route another channel through the current one
 * 
 * @param channel 
 */
void Channel::add(Channel& channel) {
  if (&channel != this) {
    mRoutedChannels.add(channel);
  }
}

/**
 * @brief Remove a routed channel
 * 
 * @param channel 
 */
void Channel::remove(Channel& channel) {
  mRoutedChannels.remove(channel);
}

};
