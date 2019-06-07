#include "Effect.h"

namespace tsal {

double Effect::getInput() {
  double input = 0.0;
  if (mNextEffect != nullptr) {
    input = mNextEffect->getOutput();
  } else if (mChannelIn != nullptr) {
    input = mChannelIn->getOutput();
  } else {
    std::cout << "Something went wrong" << std::endl;
  }
  return input;
}

// Fix this eventually 
void Effect::add(Effect* effect) {
  mNextEffect = effect;
}

/**
 * @brief Remove an effect from the chain
 * 
 * If the effect is not related to the current node,
 * it will pass on the remove command to the next node
 * 
 * @param effect 
 */
void Effect::remove(Effect* effect) {
  if (effect == mNextEffect) {
    effect->removeChannel();
    mNextEffect = effect->getNextEffect();
    effect->setNextEffect(nullptr);
  } else {
    mNextEffect->remove(effect);
  }
}

};
