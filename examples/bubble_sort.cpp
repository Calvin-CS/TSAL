#include "tsal.hpp"

using namespace tsal;

void bubbleSort(ThreadSynth& synth, int size, int data[]) {
  int temp;
  for (int i = 0; i < size; i++) {
    for (int j = size - 1; j > i; j--) {
      
      synth.play(C3 + 40 * ((double) data[j] / 1000.0), Timing::MICROSECOND, 100);
      
      if (data[j] < data[j - 1]) {
        temp = data[j];
        data[j] = data[j - 1];
        data[j - 1] = temp;
      }
    }
  }
}

int main() {
  Mixer mixer;
  ThreadSynth synth(&mixer);
  mixer.add(synth);
  
  // Generate the data
  const int size = 400;
  int data[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % 1000;
  }
  // Sort the data
  bubbleSort(synth, size, data);
}
