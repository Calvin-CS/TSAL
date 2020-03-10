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
    void setSize(AudioBuffer<T>& buffer) { setSize(buffer.getFrameCount(), buffer.getChannelCount()); };
    void setFrameCount(unsigned long frameCount);
    void setChannelCount(unsigned channelCount);
    void clear() { std::fill(mBuffer.begin(), mBuffer.end(), 0); };
    void copyBuffer (AudioBuffer<T>& buffer);
    unsigned long getFrameCount() { return mFrameCount; };
    unsigned getChannelCount() { return mChannelCount; };
    unsigned long size() { return mFrameCount * mChannelCount; };
    T* getRawPointer() { return mBuffer.data(); };
    const T& operator[](int index) const;
    T& operator[](int index);

    void deinterleaveBuffer(std::vector<AudioBuffer<T>>& buffers);
    void interleaveBuffers(std::vector<AudioBuffer<T>>& buffers);
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
  // We only call resize if the buffer is larger than our current buffer
  // This shouldn't break anything, just allows for dynamic resizing from the mixer
  // THere are ways to make a fixed audio buffer size, and maybe that's what should be done on the mixer
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
void AudioBuffer<T>::interleaveBuffers(std::vector<AudioBuffer<T>>& buffers) {
  if (buffers.size() == 0) {
    std::cout << "Cannot interleave buffers of size 0" << std::endl;
    return;
  }
  
  setChannelCount(buffers.size());
  setFrameCount(buffers[0].getFrameCount());

  for (unsigned long i = 0; i < mFrameCount; i++) {
    for (unsigned j = 0; j < mChannelCount; j++) {
      mBuffer[i * mChannelCount + j] = buffers[j][i];
    }
  }
}

template <typename T>
void AudioBuffer<T>::deinterleaveBuffer(std::vector<AudioBuffer<T>>& buffers) {
  for (auto& buffer : buffers) {
    buffer.setChannelCount(1);
    buffer.setFrameCount(mFrameCount);
  }

  for (unsigned long i = 0; i < mFrameCount; i++) {
    for (unsigned j = 0; j < mChannelCount; j++) {
      buffers[j][i] = mBuffer[i * mChannelCount + j];
    }
  }
}

}

#endif
