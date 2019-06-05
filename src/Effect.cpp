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

void Effect::add(ChannelDevice* channel) {
  mChannelIn = channel;
}

void Effect::add(Effect* effect) {
  if (mNextEffect != nullptr) {
    effect->add(mNextEffect);
  } else if (mChannelIn != nullptr) {
    effect->add(mChannelIn);
    mChannelIn = nullptr;
  }
  mNextEffect = effect;
}

};
