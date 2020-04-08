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
  PolySynth synth;
  // Synth synth;
  // synth.setMode(Oscillator::SAW);
  synth.setPanning(-0.8);
  
  // Add the synth to the mixer
  mixer.add(synth);
  
  // Play a note on the synth
  synth.play(C4);
  synth.play(E4);
  synth.play(G4);
  synth.play(B4);
  
  // Wait for the user to stop the synth
  char input;
  std::cout << "Press <enter> to quit:" << std::flush;
  std::cin.get(input);
  
  synth.stop(C4);
  synth.stop(E4);

  return 0;
  
}
