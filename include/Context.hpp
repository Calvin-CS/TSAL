#ifndef CONTEXT_H
#define CONTEXT_H

#include <functional>
#include <iostream>

namespace tsal {

class Mixer;

class Context {
  public:
    Context();
    Context(unsigned sampleRate, unsigned channelCount, Mixer *mixer);
    unsigned getChannelCount() const { return mChannelCount; };
    unsigned getSampleRate() const { return mSampleRate; };
    void update(const Context& context) {
      mSampleRate = context.getSampleRate();
      mChannelCount = context.getChannelCount();
      mMixer = context.mMixer;
    };
    static Context clear() {
      return Context();
    }
    void requestModelChange(std::function<void()> change);
  private:
    unsigned mSampleRate;
    unsigned mChannelCount;
    Mixer *mMixer;
};

}

#endif
