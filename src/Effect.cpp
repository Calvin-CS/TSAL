#include "Effect.hpp"
#include "Channel.hpp"
namespace tsal {

std::vector<ParameterManager::Parameter> Effect::EffectParameters
({
  { .name="Wet/Dry", .min=0.0, .max=1.0, .defaultValue=1.0 },
 });

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
