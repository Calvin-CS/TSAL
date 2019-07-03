#include "tsal.hpp"
#include "MidiFile.h"
#include <omp.h>
#include <vector>

// Temporary fix
#include <chrono>
#include <thread>

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
// Temporary fix


int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Invalid arguments\n\n"
              << "rain <midifile> <tracks>\n" 
              << "\tmidifile = a path to a midifile\n" 
              << "\ttracks = the number of tracks in the midifile\n"
              << std::endl;
    return 0;
  }
  const int numTracks = atoi(argv[2]);
  tsal::MidiParser midiParser(numTracks, argv[1]);

  tsal::Mixer mixer;
  std::vector<tsal::ThreadSynth> voices(numTracks);  
  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setVolume(0.3);
    mixer.add(voices[i]);
  }
/* 
  for (unsigned i = 0; i < midiParser.size(); i++) {
    auto& me = midiParser[i];  
    if (me.isNoteOn())
      voices[0].noteOn(me.getKeyNumber(), me.tick);
    
    if (me.isNoteOff())
      voices[0].noteOff(me.getKeyNumber(), me.tick);
  }
  */

  //mixer.mSequencer.setTick(0);
  mixer.test();

  omp_set_num_threads(numTracks);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int timeOffset = midiParser[id * std::floor(midiParser.size()/omp_get_num_threads())].tick;
    std::cout << "OFFSET: " << timeOffset << std::endl;
 
    #pragma omp for
    for (unsigned i = 0; i < midiParser.size(); i++) {
      auto& me = midiParser[i];  
      if (me.isNote())
        std::cout << i << " " << me.tick - timeOffset << " " << me.getKeyNumber() << std::endl;

      if (me.isNoteOn())
        voices[id].noteOn(me.getKeyNumber(), me.tick - timeOffset);
      
      if (me.isNoteOff())
        voices[id].noteOff(me.getKeyNumber(), me.tick - timeOffset);
    }
  }
  return 0;
}
