#include "Instrument.hpp"
#include "Mixer.hpp"

namespace tsal {

Instrument::Instrument(Mixer *mixer) : OutputDevice(mixer){
};

Instrument::~Instrument() {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
}

void Instrument::setParentChannel(Channel* channel) {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
  parentChannel = channel;
}

} 
