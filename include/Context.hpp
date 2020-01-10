#ifndef CONTEXT_H
#define CONTEXT_H

class Context {
  public:
    unsigned getSampleRate() const { return mSampleRate; };
    void update(const Context& context) {
      mSampleRate = context.getSampleRate();
    };
  private:
    unsigned mSampleRate = 44100;
};

#endif
