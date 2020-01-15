#include "Effect.hpp"
#include "Channel.hpp"

namespace tsal {

Effect::~Effect() {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
}

void Effect::setParentChannel(Channel* channel) {
  if (mParentChannel != nullptr)
    mParentChannel->remove(*this);
  mParentChannel = channel;
}

}
