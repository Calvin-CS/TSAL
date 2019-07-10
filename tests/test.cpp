#include "tsal.hpp"
#include <omp.h>

int main() {
  tsal::Mixer mixer;
  tsal::PolySynth polySynth;
  tsal::Channel channel;

  mixer.add(channel);
  channel.add(polySynth);

  polySynth.noteOn(tsal::C4);
  polySynth.noteOn(tsal::C5);
  polySynth.noteOn(tsal::G4);

  polySynth.noteOff(tsal::C5);

  polySynth.noteOff(tsal::G4);


  channel.remove(polySynth);
  mixer.remove(channel);
  return 0;
}
