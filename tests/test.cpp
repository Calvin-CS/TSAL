#include "tsal.hpp"
#include <omp.h>

int main() {
  tsal::Mixer mixer;
  tsal::Channel channel;
  tsal::Channel channel2;
  tsal::SoundFont soundfont("/usr/share/soundfonts/FluidR3_GM.sf2");


  mixer.add(channel);
  

  channel.add(channel2);
  
  channel2.add(soundfont);
  
  for (unsigned i = 0; i < soundfont.getPresetCount(); i++) {
    std::cout << i << " " << soundfont.getPresetName(i) << std::endl;
  }
  soundfont.setVolume(0.5);
  soundfont.setPreset(4);
  soundfont.noteOn(tsal::C4);
  tsal::Util::thread_sleep(1000);
  soundfont.noteOff(tsal::C4);
  tsal::Util::thread_sleep(2000);

  mixer.remove(channel);

  return 0;
}
