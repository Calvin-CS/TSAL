#include "AudioBuffer.hpp"
#include "tsal.hpp"
#include <cassert>

using namespace tsal;

void testConstructors() {
  unsigned channels = 2;
  unsigned frames = 1000;
  AudioBuffer<float> a1;
  a1.setChannelCount(channels);
  a1.setFrameCount(frames);
  
  AudioBuffer<float> a2(frames, channels);
  assert(a1.getChannelCount() == a2.getChannelCount());
  assert(a1.getFrameCount() == a1.getFrameCount());
  assert(a1.size() == a2.size());
  assert(a1.size() == channels * frames);
}

void testResizing() {
  unsigned channels = 2;
  unsigned frames = 1000;
  
  AudioBuffer<float> a1(frames, channels);
  AudioBuffer<float> a2;
  a2.setSize(a1);
  assert(a1.size() == a2.size());

  AudioBuffer<float> a3(2000, 4);
  a3.setSize(frames, channels);

  assert(a1.size() == a3.size());
}

void testInterleaving() {
  std::vector<AudioBuffer<float>> buffers(2, AudioBuffer<float>(2, 1));
  assert(buffers.size() == 2);
  for (auto& buffer : buffers) {
    assert(buffer.getChannelCount() == 1);
    assert(buffer.getFrameCount() == 2);
    assert(buffer.size() == 2);
  }

  AudioBuffer<float> a1(2, 2);
  for (unsigned i = 0; i < a1.size(); i++) {
    a1[i] = (float) i;
    std::cout << a1[i] << std::endl;
  }

  a1.deinterleaveBuffer(buffers);
  for (unsigned j = 0; j < buffers.size(); j++) {
    auto& buffer = buffers[j];
    std::cout << "Size" << buffer.size() << std::endl;
    for (unsigned i = 0; i < buffer.size(); i++) {
      // assert(buffer[i] == i + 2 * j);
      std::cout << buffer[i] << ": " << i + 2 * j<< std::endl;
    }
  }
}

int main() {
  testConstructors();
  testResizing();
  testInterleaving();
  return 0;
}
