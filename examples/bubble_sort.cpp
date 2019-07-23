#include "tsal.hpp"

using namespace tsal;

void bubbleSort(Synth& synth, int size, int* data) {
  int temp;
  for (int i = size; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      synth.noteOn(C2 + 55 * ((double) data[j] / 1000.0));
      Util::thread_sleep(100, Util::TimeScale::MICROSECOND);
      
      if (data[j] > data[j + 1]) {
        
        temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}

int main() {
  Mixer mixer;
  Synth synth;
  mixer.add(synth);
  synth.setEnvelopeActive(false);
  
  // Generate the data
  const int size = 1000;
  int* data = new int[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % 1000;
  }
  // Sort the data
  bubbleSort(synth, size, data);
}
