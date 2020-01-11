#include "tsal.hpp"
#include <omp.h>

using namespace tsal;

int main() {
  Mixer mixer;
  PolySynth synth(mixer.getContext());
  Delay delay(mixer.getContext());
  mixer.add(synth);
  mixer.add(delay);
  synth.play(tsal::C4);
  tsal::Util::thread_sleep(2000);
  synth.stop(tsal::C4);
  tsal::Util::thread_sleep(3000);
  exit (0);
}
