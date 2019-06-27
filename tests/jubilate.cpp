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
  std::vector<tsal::Oscillator> voices(numVoices);  
  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(-20);
    voices[i].setActive(false);
    mixer.add(voices[i]);
  }

  omp_set_num_threads(numVoices);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    
    thread_sleep(id * midiParser.quaterNoteMs(4));
    voices[id].setActive();

    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto& me = midiParser[i];
      if (me.isNoteOn())
        voices[id].playNote(me.getKeyNumber(), me.getVelocity());

      thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
      voices[id].stop();
    }
  }
  return 0;
}
