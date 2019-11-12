#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <vector>
#include <iostream>

namespace tsal {

template <typename T>
class AudioBuffer {
  public:
    AudioBuffer()
      : mFrameCount(0),
        mChannelCount(0) {};
    AudioBuffer(unsigned long frameCount, unsigned channelCount)
      : mBuffer(frameCount * channelCount, 0),
        mFrameCount(frameCount),
        mChannelCount(channelCount) {};
    void setSize(unsigned long frameCount, unsigned channelCount);
    void setSize(AudioBuffer<T> &buffer) { setSize(buffer.getFrameCount(), buffer.getChannelCount()); };
    void setFrameCount(unsigned long frameCount);
    void setChannelCount(unsigned channelCount);
    void clear() { std::fill(mBuffer.begin(), mBuffer.end(), 0); };
    unsigned long getFrameCount() { return mFrameCount; };
    unsigned getChannelCount() { return mChannelCount; };
    auto size() { return mBuffer.size(); };

    const T& operator[](int index) const;
    T& operator[](int index);
  private:
    void resize();
    std::vector<T> mBuffer;
    unsigned long mFrameCount;
    unsigned mChannelCount;
};

template <typename T>
const T& AudioBuffer<T>::operator[](int index) const {
  return mBuffer[index];
}

template <typename T>
T& AudioBuffer<T>::operator[](int index) {
  return mBuffer[index];
}

template <typename T>
void AudioBuffer<T>::resize() {
  unsigned long bufferSize = mFrameCount * mChannelCount;
  if (bufferSize > mBuffer.size()) {
    std::cout << "resizing buffer" << std::endl;
    mBuffer.resize(bufferSize);
  }
}

template <typename T>
void AudioBuffer<T>::setSize(unsigned long frameCount, unsigned channelCount) {
  setFrameCount(frameCount);
  setChannelCount(channelCount);
}

template <typename T>
void AudioBuffer<T>::setFrameCount(unsigned long frameCount) {
  mFrameCount = frameCount;
  resize();
}

template <typename T>
void AudioBuffer<T>::setChannelCount(unsigned channelCount) {
  mChannelCount = channelCount;
  resize();
}

}

#endif
