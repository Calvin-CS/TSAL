#include "LadspaManager.hpp"
#include "Oscillator.hpp"
#include "tsal.hpp"
#include <omp.h>
#include <ladspa.h>

using namespace tsal;

int main() {
  Mixer mixer;
  Synth synth;
  synth.setMode(Oscillator::SAW);

  Delay delay;
  LadspaEffect effect;
  LadspaEffect effect2;
  effect.loadPlugin("/home/mark/Downloads/ladspa_sdk_1.15/plugins/filter.so");
  effect2.loadPlugin("/home/mark/Downloads/ladspa_sdk_1.15/plugins/amp.so");
  mixer.add(effect);
  mixer.add(effect2);

  mixer.add(synth);
  // mixer.add(delay);
  synth.play(tsal::C4);
  tsal::Util::thread_sleep(2000);
  synth.stop();
  tsal::Util::thread_sleep(2000);
  exit (0);
}
