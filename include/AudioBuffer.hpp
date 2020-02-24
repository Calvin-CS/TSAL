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
    void copyBuffer (AudioBuffer<T>& buffer);
    unsigned long getFrameCount() { return mFrameCount; };
    unsigned getChannelCount() { return mChannelCount; };
    unsigned long size() { return mFrameCount * mChannelCount; };
    T* getRawPointer() { return mBuffer.data(); std::cout << "wah" << mBuffer.data() << std::endl; };
    const T& operator[](int index) const;
    T& operator[](int index);

    std::vector<AudioBuffer<T>> deinterleaveBuffer();
    void toMono(AudioBuffer<T> &buffer, T* monoBuffer);
    void toStereo(AudioBuffer<T> &buffer, T* monoBuffer);
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
void AudioBuffer<T>::copyBuffer(AudioBuffer<T>& buffer) {
  setChannelCount(buffer.getChannelCount());
  setFrameCount(buffer.getFrameCount());
  for (unsigned long i = 0; i < mFrameCount; i++) {
    for (unsigned j = 0; j < mChannelCount; j++) {
      mBuffer[i * mChannelCount + j] = buffer[i * mChannelCount + j];
    }
  }
}

template <typename T>
void AudioBuffer<T>::toMono(AudioBuffer<T> &buffer, T* monoBuffer) {
  // const auto channels = buffer.getChannelCount();
  // const auto frames = buffer.getFrameCount();
  // // This method assumes that the T* == buffer.getFrameCount()
  // T channelSum = 0;
  // for (unsigned long i = 0; i < frames; i++) {
  //   for (unsigned j = 0; j < channels; j++) {
  //     channelSum += buffer[i * channels + j];
  //   }
  //   monoBuffer[i] = channelSum / channels;
  // }
}

template <typename T>
void AudioBuffer<T>::toStereo(AudioBuffer<T> &buffer, T* monoBuffer) {
  // const auto channels = buffer.getChannelCount();
  // const auto frames = buffer.getFrameCount();
  // // This method assumes that the buffer.getFrameCount() == monoBuffer size
  // for (unsigned long i = 0; i < frames; i++) {
  //   for (unsigned j = 0; j < channels; j++) {
  //     buffer[i * channels + j] = monoBuffer[i];
  //   }
  // }
}

template <typename T>
std::vector<AudioBuffer<T>> AudioBuffer<T>::deinterleaveBuffer() {
  std::vector<AudioBuffer<T>> data(getChannelCount(), AudioBuffer<T>(size() / getChannelCount(), 1));
  const auto channels = getChannelCount();
  const auto frames = getFrameCount();

  for (unsigned long i = 0; i < frames; i++) {
    for (unsigned j = 0; j < channels; j++) {
      data[j][i] = mBuffer[i * channels + j];
    }
  }
  return data;
}

}

#endif
