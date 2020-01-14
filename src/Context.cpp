#include "Context.hpp"
#include "Mixer.hpp"

namespace tsal {

Context::Context() {
  
};

Context::Context(unsigned sampleRate, unsigned channelCount, Mixer *mixer) :
  mSampleRate(sampleRate),
  mChannelCount(channelCount),
  mMixer(mixer){};

void Context::requestModelChange(std::function<void()> change) {
  if (mMixer == nullptr)
    return;
  mMixer->requestModelChange(change);
}

}
