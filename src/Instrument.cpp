#include "Instrument.hpp"
#include "Channel.hpp"

namespace tsal {

std::vector<ParameterManager::Parameter> Instrument::InstrumentParameters
({
  { .name="Volume", .min=0.0, .max=2.0, .defaultValue=1.0 },
  { .name="Panning", .min=-1.0, .max=1.0, .defaultValue=0.0 },
});

Instrument::~Instrument() {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
}

void Instrument::setParentChannel(Channel* channel) {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
  mParentChannel = channel;
}

void Instrument::parameterUpdate(unsigned id) {
  switch(id) {
  case VOLUME:
    mAmp.setVolume(getParameter(VOLUME));
    break;
  case PANNING:
    mPanning.setPanning(getParameter(PANNING));
    break;
  }
}

}

