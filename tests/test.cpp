#include "tsal.hpp"
#include <omp.h>

using namespace tsal;

int main() {
  Mixer mixer;
  Delay delay(&mixer);

  Channel channel2(&mixer);
  Channel channel(&mixer);
  
  {
    ThreadSynth synth2(&mixer);
    mixer.add(synth2);
    std::cout << "Playing synth" << std::endl;
    synth2.play(C5, Sequencer::WHOLE, 2);
    std::cout << "DOne" << std::endl;
  }
    
  // channel2.add(delay);
  // channel.add(synth);
  // std::cout << "Playing synth" << std::endl;

  // synth.play(C4, Sequencer::HALF, 2);
  // synth.setMode(Oscillator::SAW);
  // channel2.add(synth);
  // synth.play(C4, Sequencer::EIGHTH, 1);
  // synth.stop();


  // mixer.add(channel);
  

  // channel.add(channel2);
  
  // channel2.add(soundfont);
  
  // for (unsigned i = 0; i < soundfont.getPresetCount(); i++) {
  //   std::cout << i << " " << soundfont.getPresetName(i) << std::endl;
  // }
  // soundfont.setVolume(0.5);
  // soundfont.setPreset(4);
  // soundfont.play(C4);
  // Util::thread_sleep(1000);
  // soundfont.stop(C4);
  // Util::thread_sleep(2000);

  // mixer.remove(channel);
  
  exit (0);
}
