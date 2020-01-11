#ifndef CONTEXT_H
#define CONTEXT_H

class Context {
  public:
    Context(unsigned sampleRate, unsigned channelCount) :
      mSampleRate(sampleRate),
      mChannelCount(channelCount){};
    unsigned getChannelCount() const { return mChannelCount; };
    unsigned getSampleRate() const { return mSampleRate; };
    void update(const Context& context) {
      mSampleRate = context.getSampleRate();
      mChannelCount = context.getChannelCount();
    };
  private:
    unsigned mSampleRate;
    // Assuming two channels until a system for variable number of channels exists
    unsigned mChannelCount;
};

#endif
