#include "Channel.hpp"

namespace tsal {

std::vector<ParameterManager::Parameter> Channel::ChannelParameters
({
  { .name="Volume", .min=0.0, .max=2.0, .defaultValue=1.0 },
  { .name="Panning", .min=-1.0, .max=1.0, .defaultValue=0.0 },
});

Channel::Channel() :
  ParameterManager(ChannelParameters) {
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

void Channel::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  mChannelIn.updateContext(context);
  mEffectChain.updateContext(context);
}

void Channel::getOutput(AudioBuffer<float> &buffer) {
  if (mActive) {
    const auto channels = buffer.getChannelCount();
    const auto frames = buffer.getFrameCount();
  
    mPanning.setChannelPanning(channels);
    
    mChannelIn.getOutput(buffer);
    mEffectChain.getOutput(buffer);
    for (unsigned i = 0; i < frames; i++) {
      for (unsigned j = 0; j < channels; j++) {
        buffer[i * channels + j] *= mAmp.getAmp() * mPanning.getPanningChannel(j);
      }
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

void Channel::parameterUpdate(unsigned id) {
  switch(id) {
  case VOLUME:
    mAmp.setVolume(getParameter(VOLUME));
    break;
  case PANNING:
    mPanning.setPanning(getParameter(PANNING));
    break;
  }
};

}
