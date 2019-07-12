#include "tsal.hpp"
#include <omp.h>

int main() {
  tsal::Mixer mixer;
  tsal::Delay delay;
  tsal::SoundFont soundfont("/usr/share/soundfonts/FluidR3_GM.sf2");

  mixer.add(soundfont);

  soundfont.setVolume(4.0);
  soundfont.noteOn(tsal::C4);
  tsal::thread_sleep(1000);
  soundfont.noteOff(tsal::C4);
  tsal::thread_sleep(2000);

  mixer.remove(delay);
  mixer.remove(soundfont);

  return 0;
}
