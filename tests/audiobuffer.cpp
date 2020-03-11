#include "AudioBuffer.hpp"
#include "tsal.hpp"
#include <cassert>

using namespace tsal;

void testConstructors() {
  unsigned channels = 2;
  unsigned frames = 1000;
  AudioBuffer<int> a1;
  a1.setChannelCount(channels);
  a1.setFrameCount(frames);
  
  AudioBuffer<int> a2(frames, channels);
  assert(a1.getChannelCount() == a2.getChannelCount());
  assert(a1.getFrameCount() == a1.getFrameCount());
  assert(a1.size() == a2.size());
  assert(a1.size() == channels * frames);
}

void testResizing() {
  unsigned channels = 2;
  unsigned frames = 1000;
  
  AudioBuffer<int> a1(frames, channels);
  AudioBuffer<int> a2;
  a2.setSize(a1);
  assert(a1.size() == a2.size());

  AudioBuffer<int> a3(2000, 4);
  a3.setSize(frames, channels);

  assert(a1.size() == a3.size());
}

void testInterleavingStereo() {
  std::vector<AudioBuffer<int>> buffers(2, AudioBuffer<int>(2, 1));
  assert(buffers.size() == 2);
  for (auto& buffer : buffers) {
    assert(buffer.getChannelCount() == 1);
    assert(buffer.getFrameCount() == 2);
    assert(buffer.size() == 2);
  }

  AudioBuffer<int> a1(2, 2);
  for (unsigned i = 0; i < a1.size(); i++) {
    a1[i] = i;
  }

  std::vector<AudioBuffer<int>*> buffer_pointers;
  for (auto& buffer : buffers) {
    buffer_pointers.push_back(&buffer);
  }
  a1.deinterleaveBuffer(buffer_pointers);

  for (unsigned j = 0; j < buffers.size(); j++) {
    auto& buffer = buffers[j];
    for (unsigned i = 0; i < buffer.size(); i++) {
      assert(buffer[i] == (int) (j + i * 2));
    }
  }

  a1.interleaveBuffers(buffer_pointers);
  for (unsigned i = 0; i < a1.size(); i++) {
    assert(a1[i] == (int) i);
  }
}

void testInterleavingMono() {
  std::vector<AudioBuffer<int>> buffers(1, AudioBuffer<int>(2, 1));
  assert(buffers.size() == 2);
  for (auto& buffer : buffers) {
    assert(buffer.getChannelCount() == 1);
    assert(buffer.getFrameCount() == 2);
    assert(buffer.size() == 2);
  }

  AudioBuffer<int> a1(2, 2);
  for (unsigned i = 0; i < a1.size(); i++) {
    a1[i] = i;
  }

  std::vector<AudioBuffer<int>*> buffer_pointers;
  for (auto& buffer : buffers) {
    buffer_pointers.push_back(&buffer);
  }
  a1.deinterleaveBuffer(buffer_pointers);

  for (unsigned j = 0; j < buffers.size(); j++) {
    auto& buffer = buffers[j];
    for (unsigned i = 0; i < buffer.size(); i++) {
      assert(buffer[i] == (int) (j + i * 2));
    }
  }

  a1.interleaveBuffers(buffer_pointers);
  for (unsigned i = 0; i < a1.size(); i++) {
    assert(a1[i] == (int) i);
  }
}

int main() {
  testConstructors();
  testResizing();
  testInterleavingStereo();
  return 0;
}
