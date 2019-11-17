#include "Effect.hpp"
#include "Mixer.hpp"

namespace tsal {

Effect::Effect(Mixer* mixer) : ChannelDevice(mixer) {
}

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
