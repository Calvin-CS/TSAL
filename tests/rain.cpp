#include "Mixer.h"
#include "Oscillator.h"
#include "MidiParser.h"
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
              << "\ttracks = the number of tracks in the midifile (<6)\n"
              << std::endl;
    return 0;
  }
  const int numTracks = atoi(argv[2]);
  tsal::MidiParser midiParser(numTracks, argv[1]);

  tsal::Mixer mixer;
  std::vector<tsal::Oscillator> voices(numTracks);  
  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(0.1);
    mixer.add(voices[i]);
  }

  omp_set_num_threads(numTracks);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    #pragma omp for
    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto me = midiParser[i];  
      if (me.isNote())
        voices[id].playNote(me.getKeyNumber(), me.getVelocity());
      
      thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
    }
  }
  return 0;
}
