#include "tsal.hpp"

/** @example hello_tsal.cpp
 *
 * A basic "Hello World!" application for TSAL
 *
 * Mixer - Basically the engine of TSAL. It initializes all the necessary things
 * to start an audio stream. It contains the master channel which other channels 
 * and instruments are routed to.\n
 * Synth - A very basic audio synthesizer. It can only play one note at a time (monophonic),
 * and it can choose from 3 basic waveforms: sine, saw, and square.
 */
int main() {
  // Create the mixer object
  tsal::Mixer mixer;
  
  // Create the synthesizer object
  tsal::Synth synth;
  
  // Add the synth to the master channel in the mixer
  mixer.add(synth);
  
  // Play a note on the synth
  synth.noteOn(tsal::C4);
  
  // Wait for the user to stop the synth
  char input;
  std::cout << "Press any <enter> to quit:" << std::flush;
  std::cin.get(input);
  
  // Stop the synth
  synth.noteOff();
  return 0;
}
