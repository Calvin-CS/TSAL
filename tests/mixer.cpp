#include "tsal.hpp"
#include <cassert>

using namespace tsal;

void testConstructors() {
  Mixer mixer;
  Mixer mixer2(44100);
  assert(mixer2.getSampleRate() == 44100);

  Synth synth(&mixer);
  mixer.add(synth);
  mixer2.add(synth);
  mixer2.remove(synth);
  mixer.add(synth);
}

void testAddRemove() {
  Mixer mixer;
  Channel channel(&mixer);
  Synth synth[2]{Synth(&mixer), Synth(&mixer)};
  Delay delay(&mixer);
  // Get a reference to the master channel
  Channel& master = mixer.getMaster();
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

