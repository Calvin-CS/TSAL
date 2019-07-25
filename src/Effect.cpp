#include "Effect.hpp"
#include "Mixer.hpp"

namespace tsal {

Effect::Effect(Mixer* mixer) : OutputDevice(mixer) {
}

Effect::~Effect() {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
}

void Effect::setParentChannel(Channel* channel) {
  if (parentChannel != nullptr)
    parentChannel->remove(*this);
  parentChannel = channel;
}

double Effect::getInput() {
  return mInput->getOutput();
}

void Effect::setInput(OutputDevice* input) {
  mInput = input;
}

}
