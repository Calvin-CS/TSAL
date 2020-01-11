#ifndef CONTEXT_H
#define CONTEXT_H

class Context {
  public:
    unsigned getChannelCount() const { return mChannelCount; };
    unsigned getSampleRate() const { return mSampleRate; };
    void update(const Context& context) {
      mSampleRate = context.getSampleRate();
      mChannelCount = context.getChannelCount();
    };
  private:
    unsigned mSampleRate = 44100;
    unsigned mChannelCount = 2;
};

#endif
