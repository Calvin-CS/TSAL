#include "tsal.hpp"

int main() {
  tsal::Mixer mixer;

  // Test add and remove
  tsal::Channel channel;
  tsal::Synth synth;
  mixer.add(channel);
  mixer.add(synth);
  mixer.remove(channel);
  mixer.remove(synth);

  return 0;
} 

