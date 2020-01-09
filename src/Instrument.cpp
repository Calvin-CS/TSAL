#include "Instrument.hpp"
#include "Mixer.hpp"

namespace tsal {

Instrument::Instrument(const Context& context) : ChannelDevice(context){
};

Instrument::~Instrument() {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
}

void Instrument::setParentChannel(Channel* channel) {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
  mParentChannel = channel;
}

} 
