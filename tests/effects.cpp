#include "tsal.hpp"
#include <cassert>
#include <omp.h>

using namespace tsal;

void testEffectChain() {
  unsigned currentTest = 0;
  Mixer mixer;
  Channel channel;

  std::cout << "Testing effect chain: " << std::endl;
  mixer.add(channel);
  
  // Add a bunch of effects around the same time
  omp_set_num_threads(50);
  #pragma omp parallel
  {
    Compressor compressor;
    channel.add(compressor);
  }
  std::cout << ++currentTest << std::flush;
  
  std::vector<Compressor> compressors(3, Compressor());
  channel.add(compressors[0]);
  channel.add(compressors[1]);
  channel.add(compressors[2]);
  assert(channel.getEffectCount() == 3);
  std::cout << ++currentTest << std::flush;
  
  channel.remove(compressors[1]);
  assert(channel.getEffectCount() == 2);
  std::cout << ++currentTest << std::flush;
}

void testCompressor() {
  Mixer mixer;
  Synth synth;
  Compressor compressor;
  mixer.add(compressor);
  mixer.add(synth);

  // Test parameter setting
  compressor.setAttackTime(-1.0);
  compressor.setAttackTime(3000.0);
  compressor.setAttackTime(1000.0);

  compressor.setReleaseTime(-1.0);
  compressor.setReleaseTime(3000.0);
  compressor.setReleaseTime(1000.0);

  compressor.setThreshold(-40.0);
  compressor.setThreshold(500.0);
  compressor.setThreshold(60.0);

  compressor.setRatio(0.0);
  compressor.setRatio(30.0);
  compressor.setRatio(2.0);

  compressor.setPreGain(-40.0);
  compressor.setPreGain(40.0);
  compressor.setPreGain(0.0);

  compressor.setPostGain(-40.0);
  compressor.setPostGain(40.0);
  compressor.setPostGain(0.0);

}

void testDelay() {
  Mixer mixer;
  Delay delay;
  mixer.add(delay);
  // mixer.add(synth);
}

int main() {
  testEffectChain();
  // testCompressor();
  // testDelay();
  return 0;
}
