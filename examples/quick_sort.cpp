#include "tsal.hpp"

using namespace tsal;

#define MAX_VALUE 1000000

void quickSort(ThreadSynth& synth, int* data, int low, int high) {
  if (low < high) {
    // Partition
    int pivotValue = data[low];
    int pivot = low;
    for (int i = low + 1; i < high; i++) {
      synth.play(C3 + 45 * ((double) data[i] / MAX_VALUE), Timing::MICROSECOND, 100);
      
      if (data[i] < pivotValue) {
        pivot++;
        std::swap(data[i], data[pivot]);
      }
    }
    std::swap(data[low], data[pivot]);
    
    quickSort(synth, data, low, pivot - 1);
    quickSort(synth, data, pivot + 1, high);
  }
}

int main() {
  Mixer mixer;
  ThreadSynth synth;
  mixer.add(synth);
  synth.setEnvelopeActive(false);

  // Generate the data
  const int size = 10000;
  int* data = new int[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % MAX_VALUE;
  }
  
  // Sort the data
  quickSort(synth, data, 0, size);
}
