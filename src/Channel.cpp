#include "Channel.hpp"
#include "Mixer.hpp"

namespace tsal {
  
Channel::Channel(Mixer* mixer) : ChannelDevice(mixer), mChannelIn(mixer), mRoutedInstruments(mixer), mRoutedChannels(mixer), mEffectChain(mixer, mChannelIn) {
  mChannelIn.add(mRoutedInstruments);
  mChannelIn.add(mRoutedChannels);
}

Channel::~Channel() {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
}

void Channel::setParentChannel(Channel* channel) {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
  mParentChannel = channel;
}

void Channel::setMixer(Mixer* mixer) {
  mChannelIn.setMixer(mixer);
  mEffectChain.setMixer(mixer);
}

void Channel::getOutput(AudioBuffer<float> &buffer) {
  if (mActive) {
    mChannelIn.getOutput(buffer);
    mEffectChain.getOutput(buffer);
    for (unsigned i = 0; i < buffer.size(); i++) {
      buffer[i] *= mAmp;
    }
  }
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
