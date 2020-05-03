#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <vector>
#include <iostream>

namespace tsal {

/** @class AudioBuffer
 * @brief Stores audio data in an interleaved buffer multiplexed by channels and
frames.
 *
 * With functionality for storing and manipulating audio data, AudioBuffer is
used or interfaces with almost every class in TSAL.
 * It is responsible for routing audio data throughout the system.
 * AudioBuffer stores a series of frames which are made up of some number of
channels.
 * In the case of stereo audio, there may be some number of frames with 2 channels
in each frame.
 * For example, the first 2 values in the stereo buffer will be samples for the
left and right channel which comprise the first frame
 * The next 2 values are the left and right samples for the second frame and so
on.
 * This method is optimized for CPU spatial locality since buffers are commonily iterated through sequentially
 */
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
    /**
     * @brief Zeros out the buffer
     */
    void clear() { std::fill(mBuffer.begin(), mBuffer.end(), 0); };
    unsigned long getFrameCount() { return mFrameCount; };
    unsigned getChannelCount() { return mChannelCount; };
    unsigned long size() { return mFrameCount * mChannelCount; };
    /**
     * @brief Get the raw pointer to the buffer data. Use carefully
     */
    T* getRawPointer() { return mBuffer.data(); };
    const T& operator[](int index) const;
    T& operator[](int index);

    void deinterleaveBuffer(std::vector<AudioBuffer<T>*>& buffers);
    void interleaveBuffers(std::vector<AudioBuffer<T>*>& buffers);
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
  mBuffer.resize(bufferSize);
}

template <typename T>
void AudioBuffer<T>::setSize(unsigned long frameCount, unsigned channelCount) {
  setFrameCount(frameCount);
  setChannelCount(channelCount);
}

template <typename T>
void AudioBuffer<T>::setFrameCount(unsigned long frameCount) {
  mFrameCount = frameCount;
  // Resize the buffer with the new frame count
  resize();
}

template <typename T>
void AudioBuffer<T>::setChannelCount(unsigned channelCount) {
  mChannelCount = channelCount;
  // Resize the buffer with the new channel count
  resize();
}

/**
 * @brief Combine multiple buffers into one buffer
 * 
 * @param buffers the group of buffers of interleave
 *
 * When there are multiple buffers, like one for each channel, this function interleaves multiple buffers into one buffer.
 */
template <typename T>
void AudioBuffer<T>::interleaveBuffers(std::vector<AudioBuffer<T>*>& buffers) {
  if (buffers.size() == 0) {
    // Maybe these should throw and exception
    std::cout << "Cannot interleave buffers of size 0" << std::endl;
    return;
  }
  if (mChannelCount % buffers.size() != 0) {
    std::cout << "Cannot demultiplex buffers into channels" << std::endl;
    return;
  }

  const unsigned channelDemultiplex = mChannelCount / buffers.size();
  
  setFrameCount(buffers[0]->getFrameCount());

  for (unsigned long i = 0; i < mFrameCount; i++) {
    for (unsigned j = 0; j < mChannelCount; j += channelDemultiplex) {
      for (unsigned k = 0; k < channelDemultiplex; k++) {
        mBuffer[i * mChannelCount + j + k] = (*buffers[j])[i];
      }
    }
  }
}

/**
 * @brief Create multiple buffers from one buffer
 * 
 * @param buffers the group of buffers to deinterleave into
 *
 * When there are multiple channels interleaved in one buffer, this function deinterleaves the one buffer into multiple, one for each channel.
 */
template <typename T>
void AudioBuffer<T>::deinterleaveBuffer(std::vector<AudioBuffer<T>*>& buffers) {
  if (buffers.size() > mChannelCount) {
    std::cout << "Cannot interleave buffers of size " << buffers.size() << std::endl;
    return;
  }
  if (mChannelCount % buffers.size() != 0) {
    std::cout << "Cannot demultiplex buffers into channels" << std::endl;
  }

  const unsigned channelMultiplex = mChannelCount / buffers.size();

  for (auto buffer : buffers) {
    buffer->setChannelCount(1);
    buffer->setFrameCount(mFrameCount);
  }

  for (unsigned long i = 0; i < mFrameCount; i++) {
    for (unsigned j = 0; j < mChannelCount; j += channelMultiplex) {
      AudioBuffer<T>& b= (*buffers[j]);
      b[i] = 0;
      for (unsigned k = 0; k < channelMultiplex; k++) {
        b[i] += mBuffer[i * mChannelCount + j + k];
      }
      b[i] /= channelMultiplex;
    }
  }
}

}

#endif
