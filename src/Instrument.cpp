#include "Instrument.hpp"
#include "Mixer.hpp"

namespace tsal {

Instrument::Instrument(Mixer *mixer) : OutputDevice(mixer){
};

Instrument::~Instrument() {
  std::cout << "Removing Instrument from Channel" << std::endl;
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
}

void Instrument::setParentChannel(Channel* channel) {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
  parentChannel = channel;
}

} 
