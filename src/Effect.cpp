#include "Effect.hpp"

namespace tsal {

double Effect::getInput() {
  return mInput->getOutput();
}

void Effect::setInput(OutputDevice* input) {
  mInput = input;
}

}
