#include "Oscillator.h"
#include "Chord.h"
#include <iostream>
#include <memory>

#include <omp.h>
#include <chrono>
#include <thread>

int main() {

// Test
/*
  Oscillator osc1;
  osc1.setGain(0.4);
  osc1.setMode(SQUARE);

  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
*/

// Test 1
/*
  std::unique_ptr<Oscillator> test0(new Oscillator());
  test0->setWaveform(std::make_unique<SquareWave>());
  test0->setGain(0.1);
  test0->setFrequency(100);

  #pragma omp parallel for
  for(int i = 1; i < 300; ++i) {
    test0->setFrequency(test0->getFrequency() + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
*/

// Test 2
/*
  std::unique_ptr<Oscillator> test1(new Oscillator());
  test1->setGain(0.5);
  test1->setFrequency(100);
  
  for(int i = 1; i < 300; ++i) {
    test1->setFrequency(test1->getFrequency() + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
*/
  omp_set_num_threads(3);

  Chord chord(3, 60, 70);
  #pragma omp parallel
  {
    unsigned id = omp_get_thread_num();
    chord.start(id);
    for(int i = 1; i < 300; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    chord.stop(id);
  }
  

/*
  std::cout << "\n Press <enter> to stop\n" << std::endl;
  char input;
  std::cin.get(input);
*/
  return 0;
}
