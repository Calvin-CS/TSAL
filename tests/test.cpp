#include "Mixer.h"
#include "Oscillator.h"

#include <chrono>
#include <thread>
void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
  tsal::Mixer mixer;
  tsal::Oscillator oscillator;
oscillator.setMode(tsal::Oscillator::SQUARE);
  oscillator.setGain(0.05);
  mixer.add(oscillator);
  thread_sleep(1000);
  return 0;
}
