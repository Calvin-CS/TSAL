#include "Channel.hpp"
#include "Mixer.hpp"

namespace tsal {
  
Channel::Channel(Mixer* mixer) : OutputDevice(mixer), mChannelIn(mixer), mRoutedInstruments(mixer), mRoutedChannels(mixer), mEffectChain(mixer) {
  mChannelIn.add(mRoutedInstruments);
  mChannelIn.add(mRoutedChannels);
  mEffectChain.setInput(mChannelIn);
}

Channel::~Channel() {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
}

void Channel::setParentChannel(Channel* channel) {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
  parentChannel = channel;
}

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
  effect.setParentChannel(this);
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
  instrument.setParentChannel(this);
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
    channel.setParentChannel(this);
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
