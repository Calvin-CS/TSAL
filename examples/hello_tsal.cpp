#include "Oscillator.hpp"
#include "PolySynth.hpp"
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
  PolySynth synth2;
  Delay delay;
  delay.setParameter(Delay::FEEDBACK, 0.3);
  mixer.add(delay);
  // Synth synth;
  // synth.setMode(Oscillator::SAW);
  synth.setPanning(-0.8);
  synth.setParameter(PolySynth::MODULATION_MODE, Oscillator::AM);
  synth.setVolume(0.1);
  // synth.setParameter(PolySynth::OSC2_OFFSET, 0.2);
  synth.setParameter(PolySynth::ENV_ATTACK, 0.1);
  // synth.setParameter(PolySynth::ENV_RELEASE, 10.0);
  synth.setParameter(PolySynth::OSC1_MODE, Oscillator::SINE);
  synth.setParameter(PolySynth::OSC2_MODE, Oscillator::WHITE_NOISE);
  // synth.setParameter(PolySynth::OSC2_MODE, Oscillator::WHITE_NOISE);
  
  // Add the synth to the mixer
  mixer.add(synth);
  mixer.add(synth2);
  
  synth2.play(C4);
  synth2.setParameter(PolySynth::MODULATION_MODE, Oscillator::MIX);
  synth2.setVolume(0.5);
  // Play a note on the synth
  synth.play(E4);
  Util::thread_sleep(1500);
  synth.stop(E4);
  Util::thread_sleep(5000);

  // synth.setParameter(PolySynth::OSC1_MODE, Oscillator::SQUARE);
  // synth.setParameter(PolySynth::OSC2_OFFSET, 0.0);
  // synth.setParameter(PolySynth::OSC2_MODE, Oscillator::SAW);
  synth.setParameter(PolySynth::MODULATION_MODE, Oscillator::PM);

  synth.play(E4);
  Util::thread_sleep(500);
  synth.stop(E4);
  Util::thread_sleep(1500);
  // synth.play(G4);
  // synth.play(B4);
  
  // Wait for the user to stop the synth
  // char input;
  // std::cout << "Press <enter> to quit:" << std::flush;
  // std::cin.get(input);
  

  return 0;
  
}
