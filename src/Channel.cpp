#include "Channel.hpp"
#include "Mixer.hpp"

namespace tsal {
  
Channel::Channel() {
  mChannelIn.add(mRoutedInstruments);
  mChannelIn.add(mRoutedChannels);
  mEffectChain.setInput(mChannelIn);
}

Channel::~Channel() {}

void Channel::setMixer(Mixer* mixer) {
  mChannelIn.setMixer(mixer);
  mEffectChain.setMixer(mixer);
}

double Channel::getOutput() {
  if (!mActive) {
    return 0.0;
  }
  return mEffectChain.getOutput() * mAmp;
}

/**
 * @brief Add an effect to the end of the effect chain
 * 
 * @param effect 
 */
void Channel::add(Effect& effect) {
  mEffectChain.add(effect);
}
/**
 * @brief Remove an effect from the effect chain 
 * 
 * @param effect 
 */
void Channel::remove(Effect& effect) {
  mEffectChain.remove(effect);
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

}
