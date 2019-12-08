#include "tsal.hpp"

using namespace tsal;

#define MAX_VALUE 100000

void bubbleSort(ThreadSynth& synth, int size, int data[]) {
  int temp;
  for (int i = 0; i < size; i++) {
    for (int j = size - 1; j > i; j--) {
      
      synth.play(C3 + 40 * ((double) data[j] / MAX_VALUE), Timing::MICROSECOND, 50);
      
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
  synth.setEnvelopeActive(false);
  
  // Generate the data
  const int size = 5000;
  int data[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % MAX_VALUE;
  }
  // Sort the data
  bubbleSort(synth, size, data);
}
