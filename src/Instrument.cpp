#include "Instrument.hpp"
#include "Mixer.hpp"

namespace tsal {

Instrument::Instrument(Mixer *mixer) : ChannelDevice(mixer){
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
