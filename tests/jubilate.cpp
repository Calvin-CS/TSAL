#include "tsal.hpp"
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
              << "jubilate <midifile> <voices>\n" 
              << "\tmidifile = a path to a midifile\n" 
              << "\tvoices = the number of voices (<6)\n"
              << std::endl;
    return 0;
  }
  tsal::MidiParser midiParser(1, argv[1]);
  const int numVoices = atoi(argv[2]);

  tsal::Mixer mixer;
  std::vector<tsal::ThreadSynth> voices(numVoices);  
  for (unsigned i = 0; i < voices.size(); i++) {
    mixer.add(voices[i]);
  }

  omp_set_num_threads(numVoices);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    
    int timeOffset = id * 4 * midiParser.getPPQ();
    voices[id].setActive();

    for (unsigned i = 0; i < midiParser.size(); i++) {
      auto& me = midiParser[i];
      if (me.isNoteOn())
        voices[id].noteOn(me.getKeyNumber(), me.tick + timeOffset);

      if (me.isNoteOff())
        voices[id].noteOff(me.getKeyNumber(), me.tick + timeOffset);
    }
  }
  return 0;
}
