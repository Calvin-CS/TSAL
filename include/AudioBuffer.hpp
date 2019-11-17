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

    static std::vector<std::vector<T>> deinterleaveBuffer(AudioBuffer<T> &buffer);
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

template <typename T>
std::vector<std::vector<T>> AudioBuffer<T>::deinterleaveBuffer(AudioBuffer<T> &buffer) {
  std::vector<std::vector<T>> data(buffer.getChannelCount(), std::vector<T>(buffer.size() / buffer.getChannelCount()));
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();

  setChannelPanning(channels);

  for (unsigned long i = 0; i < frames; i++) {
    for (unsigned j = 0; j < channels; j++) {
      data[j][i] = buffer[i * channels + j];
    }
  }
  return std::move(data);
}

}

#endif
