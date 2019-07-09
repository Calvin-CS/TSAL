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

  tsal::thread_sleep(1000);

  polySynth.noteOff(tsal::C5);
 
  tsal::thread_sleep(3000);

  polySynth.noteOff(tsal::G4);

  tsal::thread_sleep(3000);
  
  return 0;
}
