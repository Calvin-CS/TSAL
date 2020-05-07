#include "Instrument.hpp"
#include "Channel.hpp"

namespace tsal {

std::vector<ParameterManager::Parameter> Instrument::InstrumentParameters
({
  Amp::AmpParameterVolume,
  Panning::PanningParameter,
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

