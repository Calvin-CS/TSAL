#include "tsal.hpp"
#include <omp.h>

using namespace tsal;

int main() {
  Mixer mixer;
  PolySynth synth(&mixer);
  synth.play(tsal::C4);
    
  AudioBuffer<float> mBuffer;
  mBuffer.setSize(12, 2);
  synth.getOutput(mBuffer);
  for (unsigned i = 0; i < mBuffer.size(); i++) {
    printf("%f, ", mBuffer[i]);
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
