#include "tsal.hpp"
#include <cassert>

void testEffectChain() {
  tsal::Mixer mixer;
  tsal::Synth synth;
  tsal::Channel channel;
  tsal::Compressor compressor[3];
  mixer.add(channel);
  channel.add(synth);
  synth.noteOn(tsal::C4);
  
  channel.add(compressor[0]);
  channel.add(compressor[1]);
  assert(channel.getEffectCount() == 2);
  std::cout << "1" << std::flush;
  
  // Test middle case remove effect (effect chain: 0 1 2)
  channel.add(compressor[2]);
  channel.remove(compressor[1]);
  assert(channel.getEffectCount() == 2);
  std::cout << "2" << std::flush;

  // Test front case (effect chain: 0 2 1)
  channel.add(compressor[1]);
  channel.remove(compressor[0]);
  assert(channel.getEffectCount() == 2);
  std::cout << "3" << std::flush;

  // Test back case (effect chain: 2 1)
  channel.remove(compressor[1]);
  assert(channel.getEffectCount() == 1);
  std::cout << "4" << std::endl;
}

void testCompressor() {
  tsal::Mixer mixer;
  tsal::Synth synth;
  tsal::Compressor compressor;
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

  mixer.remove(synth);
  mixer.remove(compressor);
}

int main() {
  testEffectChain();
  testCompressor();
  return 0;
}
