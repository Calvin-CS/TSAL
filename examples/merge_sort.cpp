#include "tsal.hpp"
#include <omp.h>

using namespace tsal;

enum MergeState {
  S_MERGE = 1,
  S_SHIFT = 2,
  S_WAIT = 3,
  S_DONE = 4,
  S_HIDE = 5
};

struct sortData {
  MergeState state;            //Current state of the threads
  int first, last,             //Start and end of our block
    left, right,               //Indices of two numbers to compare
    fi, hi, li,                //Indices of first middle and last numbers in a set
    depth;                     //Current depth of the merge
  int* a;                      //Array of numbers to sort
  int seg, segs;               //Current / total segments
  int size;

  sortData(int* arr, int f, int l) {
    fi = hi = li = 0;        //Initialize indices
    left = right = 0;        //Initialize bounds
    a = arr;                 //Get a pointer to the array we'll be sorting
    first = f;               //Set the first element we need to worry about
    last = l;                //Set the last element we need to worry about
    depth = 0;               //We start at depth 0
    seg = 0; segs = 1;       //We start on segment -1, with a total of 1 segment
    while(segs < (l-f)) {    //If the current number of segments is more than the # of elements, we're done
      ++depth;               //Otherwise, increment the depth...
      segs *= 2;             //...and double the number of segments
    }
    state = S_SHIFT;         //Start Merging
    size = 2;
  }

  void restart(int l) {
    depth = 0;
    hi = last;
    right = hi+1;
    last = li = l;
    fi = left = first;
    state = S_MERGE;
    size *= 2;
  }

  void sortStep() {
    int tmp, pivot, jump;
    switch(state) {
      case S_SHIFT:
        pivot = jump = segs/2;
        fi = first; li = last;
        hi = (fi + li) / 2;    //Set our half index to the median of our first and last
        for (tmp = depth; tmp > 0; --tmp) {
          jump /= 2;
          if (seg < pivot) {
            pivot -= jump;
            li = hi;           //Set out last index to our old half index
          } else {
            pivot += jump;
            fi = hi+1;         //Set out first index to our old half index plus one
          }
          hi = (fi + li) / 2;  //Set our new half index to the median of our first and last
        }
        left = fi; right = hi+1;
        state = S_MERGE;           //We're ready to start Merging
        break;
      case S_MERGE:
        if (left > right || right > last) {
          seg = 0;                 //Reset our segment(s)
          segs /= 2;               //We're now using half as many segments
          state = (depth-- == 0) ? S_WAIT : S_SHIFT;
        } else if (right > li) {
          ++seg; state = S_SHIFT;  //Move on to the next segment and recalculate our first and last indices
        } else if (left <= hi && a[left] < a[right]) {
          ++left;
        } else {
          tmp = a[right];
          for (int x = right; x > left; --x)
            a[x] = a[x-1];
          a[left] = tmp;
          ++left; ++right; ++hi;
        }
        break;
      default:
        break;
    }
  }
};



/*!
 * \brief Visualization of the bottom-up mergesort algorithm.
 * \details Utilizes the sortData struct and sorts a number of items using the mergesort algorithm.
 * \details Uses lines to represent the items being sorted.
 * \details At the start, the items being sorted are all divided.
 * \details Once items have been sorted in one divided section, then sections are merged and the process repeats itself.
 * \details Different colors represent different sections being sorted.
 * \details Once all items have been sorted and merged, the animation stops and all lines are colored white.
 */
void mergeSortFunction(std::vector<Synth>& voices, int threads, int size) {
  const int IPF = 1;      // Iterations per frame
  const int maxNumber = 100000;
  int* numbers = new int[size];       // Array to store the data
  for (int i = 0; i < size; i++)
    numbers[i] = rand() % maxNumber;

  int bs = size / threads;
  int ex = size % threads;
  sortData** sd = new sortData*[threads];
  int f = 0;
  int l = (ex == 0) ? bs-1 : bs;
  for (int i = 0; i < threads; ++i) {
    sd[i] = new sortData(numbers,f,l);
    f = l+1;
    if (i < ex-1) l += (bs + 1);
    else          l += bs;
  }
  #pragma omp parallel num_threads(threads)
  {
    int tid = omp_get_thread_num();
    auto& voice = voices[tid];
    //std::cout << tid << std::endl;
    while (true) {
      if (sd[tid]->state == S_WAIT) {  //Merge waiting threads

        if ((tid % sd[tid]->size) > 0) {
          sd[tid]->state = S_DONE;
        } else {
          int next = tid+sd[tid]->size/2;
          if (next < threads && sd[next]->state == S_DONE) {
            sd[next]->state = S_HIDE;
            
            sd[tid]->restart(sd[next]->last);
          }
        }
      }
      for (int i = 0; i < IPF; i++)
        sd[tid]->sortStep();

      double number;
      if (sd[tid]->state != S_HIDE) {
        for (int i = sd[tid]->first; i < sd[tid]->last; ++i) {
          number = numbers[i];
          // If we are processing the item, play a sound
          if (i == sd[tid]->left) {
            voice.noteOn(C2 + (tid * 3) + 60 * (number / maxNumber));
            Util::thread_sleep(100, Util::TimeScale::MICROSECOND);
          }
        } 
      }
    }
  }
  for (int i = 0; i < threads; ++i)
    delete sd[i];
  delete [] sd;
  delete [] numbers;
}

/** @example merge_sort.cpp
 * 
 * Merge sort is a sorting algorithm that can be done in parallel. As a result,
 * each thread involved in the algorithm is assigned an oscillator which plays
 * the pitch of the processed item plus a constant. Each thread has its own base
 * pitch so you can differentiate between them near the end of the sorting process.
 *
 * Parse the parameters\n
 * Create the mixer and oscillators\n
 * Start the merge sort algorithm
 * For each thread:
 * - Process an item in the merge step and set the oscillator pitch accordingly
 * - When complete with job, mute the oscillator 
 */
int main() {

    int threads, t = 4;
    for (threads = 1; threads < t; threads *=2);  //Force threads to be a power of 2

    Mixer mixer;
    std::vector<Synth> voices(threads, Synth(&mixer));
    for (unsigned i = 0; i < voices.size(); i++) {
      mixer.add(voices[i]);
      voices[i].setVolume(0.5);
      voices[i].setEnvelopeActive(false);      
    } 
    mergeSortFunction(voices, threads, 10000);
}
