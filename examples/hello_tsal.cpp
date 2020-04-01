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
using namespace tsal;

int main() {
  // Create the mixer object
  Mixer mixer;
  
  // Create the synthesizer object
  Synth synth;
  // Synth synth;
  synth.setMode(Oscillator::SAW);
  
  // Add the synth to the mixer
  mixer.add(synth);
  
  // Play a note on the synth
  synth.play(C4);
  // synth.play(E4);
  
  // Util::thread_sleep(1000);

  // synth.stop(C4);
  
  // Wait for the user to stop the synth
  char input;
  std::cout << "Press <enter> to quit:" << std::flush;
  std::cin.get(input);
  
  return 0;
  
}
