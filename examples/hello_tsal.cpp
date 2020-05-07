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
  SoundFont sf("/usr/share/sounds/sf2/FluidR3_GM.sf2");
  sf.setPreset("Halo Pad"); 
  mixer.add(sf);
  // sf.play(C4);
  // sf.play(E4);
  // Create the synthesizer object
  PolySynth synth;
  PolySynth synth2;
  Delay delay;
  delay.setParameter(Delay::FEEDBACK, 0.3);
  // mixer.add(delay);
  // Synth synth;
  // synth.setMode(Oscillator::SAW);
  // synth.setPanning(-0.8);
  synth.setParameter(PolySynth::MODULATION_MODE, Oscillator::AM);
  synth.setParameter(PolySynth::VOLUME, 0.5);
  // synth.setParameter(PolySynth::PANNING, -1.0);
  // synth.setParameter(PolySynth::OSC2_OFFSET, 0.2);
  synth.setParameter(PolySynth::ENV_ATTACK, 0.1);
  // synth.setParameter(PolySynth::ENV_RELEASE, 10.0);
  synth.setParameter(PolySynth::OSC1_MODE, Oscillator::SINE);
  synth.setParameter(PolySynth::OSC2_MODE, Oscillator::SINE);
  synth2.setParameter(PolySynth::OSC1_MODE, Oscillator::SINE);
  // synth2.setParameter(PolySynth::PANNING, 1.0);
  synth.setParameter(PolySynth::MODULATION_MODE, Oscillator::NONE);
  // synth.setParameter(PolySynth::OSC2_MODE, Oscillator::WHITE_NOISE);
  
  synth2.setParameter(PolySynth::VOLUME, 0.5);
  // PolySynth synth3 = synth;
  // PolySynth synth(std::move(synth2));
  // Add the synth t
  Channel chan;
  mixer.add(synth);
  mixer.add(synth2);
  chan.setParameter(Channel::PANNING, 1.0);
  mixer.add(chan);
  
  synth.play(C4);
  synth.setParameter(PolySynth::MODULATION_MODE, Oscillator::MIX);
  // Play a note on the synth
  synth2.play(E4);
  Util::thread_sleep(1500);
  synth2.stop(E4);
  Util::thread_sleep(5000);

  // synth.setParameter(PolySynth::OSC1_MODE, Oscillator::SQUARE);
  // synth.setParameter(PolySynth::OSC2_OFFSET, 0.0);
  // synth.setParameter(PolySynth::OSC2_MODE, Oscillator::SAW);
  synth2.setParameter(PolySynth::MODULATION_MODE, Oscillator::PM);

  synth2.play(E4);
  Util::thread_sleep(500);
  synth2.stop(E4);
  Util::thread_sleep(1500);
  // synth.play(G4);
  synth.stop(C4);
  
  for (unsigned i = 0; i < 10; i++) {
    static double volume = 0.0;
    synth2.setParameter(PolySynth::VOLUME, volume);
    synth2.play(C4);
    Util::thread_sleep(500);
    synth2.stop(C4);
    Util::thread_sleep(100);
    volume += 0.1;
  }
  // Wait for the user to stop the synth
  // char input;
  // std::cout << "Press <enter> to quit:" << std::flush;
  // std::cin.get(input);
  

  return 0;
  
}
