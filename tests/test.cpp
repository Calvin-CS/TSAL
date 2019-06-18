#include "Mixer.h"
#include "Oscillator.h"
#include "Delay.h"
#include "MidiNotes.h"
#include "MidiParser.h"

#include <chrono>
#include <thread>
void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
  tsal::Mixer mixer;
  tsal::Oscillator oscillator;
  tsal::Delay delay;

  oscillator.setMode(tsal::Oscillator::SAW);
  oscillator.setGain(0.1);

  mixer.add(oscillator);
  mixer.add(delay);

  thread_sleep(500);

  oscillator.setActive(false);

  thread_sleep(2000);

  tsal::MidiParser midiParser(1, "/home/mark/Downloads/velocity.mid");
  for (unsigned i = 0; i < midiParser.size(); i++) {
    auto& me = midiParser[i];
    if (me.isNoteOn())
      std::cout << me.getDurationInSeconds() << std::endl;
     
  }
  std::cout << "ree" << std::endl;

  return 0;
}
