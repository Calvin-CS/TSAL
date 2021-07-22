#include "tsal.hpp"
#include <iostream>
using namespace tsal;

long long factorial(int n, ThreadSynth& synth) {
    const int DURATION = 1;
    long long answer = 0;

    // Use a Note Scale to choose different notes as the recursion happens
    MidiNote note = Util::scaleToNote(n, std::make_pair(0, 30), std::make_pair(C4, C7));

    if (n > 1) {
      synth.play(note, Timing::SECOND, DURATION);
      // Recursive call
      answer = n * factorial(n - 1, synth);
      synth.play(note, Timing::SECOND, DURATION);
    } else {
      synth.play(note, Timing::SECOND, DURATION);
      // Wait for 2 seconds at the bottom to show you have reached the base case
      synth.stop(Timing::SECOND, DURATION*2);
      answer = 1;
    }

    return answer;
}

int main(int argc, char* argv[]) {
    // Setup to use TSAL
    Mixer mixer;
    ThreadSynth synth(&mixer);

    mixer.add(synth);

    synth.setEnvelopeActive(false);

    int n = atoi(argv[1]);
    std::cout << "Factorial of "<< argv[1] << " = " << factorial(n, synth) << std::endl;
    return 0;
}