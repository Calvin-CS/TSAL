#include "Effect.h"

namespace tsal {

double Effect::getInput() {
  return (mNextEffect == nullptr) ? mOutputDevices[0]->getOutput() : mNextEffect->getOutput();
}
void Effect::add(Effect* effect) {
  mNextEffect = effect;
}

};
