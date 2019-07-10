#include "tsal.hpp"
#include <cassert>

void testConstructors() {
  tsal::Mixer mixer;
  tsal::Mixer mixer1(44100);
  assert(mixer1.getSampleRate() == 44100);
}

void testAddRemove() {
  tsal::Mixer mixer;
  tsal::Channel channel;
  tsal::Synth synth[2];
  tsal::Delay delay;
  // Get a reference to the master channel
  tsal::Channel& master = mixer.getMaster();
  // The master channel will probably come with some number of default effects
  int defaultEffectCount = master.getEffectCount();
  
  mixer.add(channel);
  assert(master.getChannelCount() == 1);

  mixer.add(synth[0]);
  assert(master.getInstrumentCount() == 1);
  assert(master.getChannelCount() == 1);

  mixer.add(synth[1]);
  assert(master.getInstrumentCount() == 2);

  mixer.remove(synth[0]);
  mixer.remove(synth[1]);
  channel.add(synth[0]);
  assert(master.getChannelCount() == 1);
  assert(master.getInstrumentCount() == 0);

  mixer.add(delay);
  // There are two effects since the master channel has a compressor by default
  assert(master.getEffectCount() == 1 + defaultEffectCount);

  mixer.remove(delay);
  mixer.remove(channel);
  assert(master.getChannelCount() == 0);
  assert(master.getEffectCount() == defaultEffectCount);
  assert(master.getInstrumentCount() == 0);

}

int main() {
  testConstructors();
  testAddRemove();
  return 0;
}

