#include "Effect.hpp"
#include "Mixer.hpp"

namespace tsal {

Effect::~Effect() {}

double Effect::getInput() {
  return mInput->getOutput();
}

void Effect::setInput(OutputDevice* input) {
  mInput = input;
}

}
