#include "tsal.hpp"
#include <iostream>
using namespace tsal;

int fib(int n, ThreadSynth& synth) {
    if (n <= 1) {
      synth.play(C4, Timing::MICROSECOND, 50);
      return n;
    }
    return fib(n-1) + fib(n-2);
}

int main(int argc, char* argv[]) {
    Mixer mixer;
    ThreadSynth synth(&mixer);
    mixer.add(synth);
    synth.setEnvelopeActive(false);

    int n = atoi(argv[1]);
    std::cout << fib(n, synth) << std::endl;
    return 0;
}