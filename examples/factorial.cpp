#include "tsal.hpp"
#include <iostream>
using namespace tsal;

long long factorial(int n, ThreadSynth& synth, SoundFont& soundFont) {
    const int DURATION = 1;
    long long answer = 0;

    MidiNote note = Util::scaleToNote(n, std::make_pair(0, 30), std::make_pair(C4, C7));

    if (n > 1) {
      //synth.play(note, Timing::SECOND, DURATION);
      soundFont.play(40);
      answer = n * factorial(n - 1, synth, soundFont);
      soundFont.play(40);
      //synth.play(note, Timing::SECOND, DURATION);
    } else {
      //synth.play(note, Timing::SECOND, DURATION);
      soundFont.play(40);
      answer = 1;
    }

    return answer;
}

int main(int argc, char* argv[]) {
    Mixer mixer;
    ThreadSynth synth(&mixer);
    SoundFont soundFont(&mixer, "cymbalRoll.sf2");

    mixer.add(synth);
    mixer.add(soundFont);

    synth.setEnvelopeActive(false);

    int n = atoi(argv[1]);
    std::cout << factorial(n, synth, soundFont) << std::endl;
    return 0;
}