#include "tsal.hpp"
#include <cassert>

using namespace tsal;

void testConstructors() {
  Mixer mixer;
  Mixer mixer2(44100);

  Synth synth;
  mixer.add(synth);
  mixer2.add(synth);
  mixer2.remove(synth);
  mixer.add(synth);
}

void testAddRemove() {
  Mixer mixer;
  Channel channel;
  Synth synth[2]{Synth(), Synth()};
  Delay delay;
  mixer.add(channel);

  mixer.add(synth[0]);
  mixer.add(synth[1]);

  mixer.remove(synth[0]);
  mixer.remove(synth[1]);
  channel.add(synth[0]);

  mixer.add(delay);

  mixer.remove(delay);
  mixer.remove(channel);
}


int main() {
  testConstructors();
  testAddRemove();
  return 0;
}

