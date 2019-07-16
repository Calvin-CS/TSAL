#include "tsal.hpp"
#include "MidiFile.h"
#include <omp.h>
#include <vector>

/** @example rain.cpp
 * 
 * One use of multithreaded is to speed up the processing of data. However, in the case of audio,
 * processing a song at twice the speed doesn't really make sense. As a result, this example was created
 * as the next best thing. To make use of the speed up from multithreading, this example parses
 * MIDI files that store the entire song on one track. When processed with a single ThreadSynth, 
 * the song will play its parts separately. But when processed with the right number of threads. The
 * ThreadSynths will be playing in unison, and the song will be completed properly.
 * 
 * Parse the parameters\n
 * Create the mixer and synths\n
 * Play the song through once with only one thread\n
 * Run parallel block
 * - Calculate a time offset so the later notes get scheduled at the right time
 * - Play the midi events 
 */
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

  for (unsigned i = 0; i < midiParser.size(); i++) {
    auto& me = midiParser[i];  
    if (me.isNoteOn())
      voices[0].noteOn(me.getKeyNumber(), me.getVelocity(), me.tick);
    
    if (me.isNoteOff())
      voices[0].noteOff(me.getKeyNumber(), me.tick);
  }

  mixer.getSequencer().setTick(0);
  omp_set_num_threads(numTracks);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int timeOffset = midiParser[id * std::floor(midiParser.size()/omp_get_num_threads())].tick;
 
    #pragma omp for
    for (unsigned i = 0; i < midiParser.size(); i++) {
      auto& me = midiParser[i];  
      if (me.isNoteOn())
        voices[id].noteOn(me.getKeyNumber(), me.getVelocity(), me.tick - timeOffset);
      
      if (me.isNoteOff())
        voices[id].noteOff(me.getKeyNumber(), me.tick - timeOffset);
    }
  }
  return 0;
}
