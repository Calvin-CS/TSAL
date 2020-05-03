#ifndef CONTEXT_H
#define CONTEXT_H

#include <functional>
#include <iostream>

namespace tsal {

class Mixer;

/** @class Context
 * @brief Manages the connection between the Mixer and other devices
 *
 * Context provides a safe interface for devices to interact with the necessary
Mixer methods.
 * An empty can also be used to initialize a device without being connected to a Mixer.
 */
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
