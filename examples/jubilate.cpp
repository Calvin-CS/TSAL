#include "tsal.hpp"
#include <omp.h>
#include <vector>

/** @example jubilate.cpp
 * 
 * ThreadSynth is an instrument that uses blocking calls to schedule its midi events.
 * If this instrument was used in a process with only one thread, there could only be 
 * one synth playing at a time. To achieve a multi-instrument sound, each ThreadSynth
 * will need its own thread. The omp parallel pragma creates these threads for each synth
 * so that when the ThreadSynth makes a call to noteOn or noteOff, only that synth's thread
 * is blocked
 * 
 * The program is based on the Jubilate Deo sang with a round 
 * https://youtu.be/ILLvDfsI_iM?t=33 (sine waves sounds less angelic)
 * 
 * Parse the parameters\n
 * Create the mixer and synths\n
 * Set the number of threads\n
 * Run parallel block
 * - Calculate an offset into the song for a round effect
 * - Play the midi events
 */
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
    voices[i].setVolume(0.3);
    mixer.add(voices[i]);
  }

  omp_set_num_threads(numVoices);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    
    // Get a ith measure offset into the song
    int timeOffset = id * 4 * midiParser.getPPQ();

    for (unsigned i = 0; i < midiParser.size(); i++) {
      auto& me = midiParser[i];
      if (me.isNoteOn())
        voices[id].noteOn(me.getKeyNumber(), me.getVelocity(), me.tick + timeOffset);

      if (me.isNoteOff())
        voices[id].noteOff(me.getKeyNumber(), me.tick + timeOffset);
    }
  }
  return 0;
}
