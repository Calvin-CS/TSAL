#include "tsal.hpp"
#include <omp.h>
#include <vector>


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
    voices[i].setGain(-20);
    // Testing
    voices[i].seq = &mixer.mSequencer;
    mixer.add(voices[i]);
  }

  mixer.mSequencer.setBPM(70);

  omp_set_num_threads(numTracks);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int timeOffset = midiParser[id * midiParser.size()/omp_get_num_threads()].tick;

    #pragma omp for
    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto& me = midiParser[i];  
      if (me.isNote())
        voices[id].noteOn(me.getKeyNumber(), me.tick - timeOffset);
      
      if (me.isNoteOff()) {
        voices[id].noteOff(me.getKeyNumber(), me.tick - timeOffset);
      }
    }
  }
  return 0;
}
