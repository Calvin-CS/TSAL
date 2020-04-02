#include "Context.hpp"
#include "Mixer.hpp"

namespace tsal {

Context::Context() :
  mSampleRate(1),
  mChannelCount(1),
  mMixer(nullptr){};

Context::Context(unsigned sampleRate, unsigned channelCount, Mixer *mixer) :
  mSampleRate(sampleRate),
  mChannelCount(channelCount),
  mMixer(mixer){};

void Context::requestModelChange(std::function<void()> change) {
  if (mMixer == nullptr) {
    // This change will not be thread safe
    change();
    return;
  }
  mMixer->requestModelChange(change);
}

}
