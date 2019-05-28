#include <memory>
#include "AudioNode.h"
#include "RtAudio.h"
#include "SineWave.h"
#include "SawWave.h"
#include "SquareWave.h"

#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

enum OscillatorMode {
  SAW,
  SINE,
  SQUARE,
  CUSTOM
};

class OscillatorNode : public AudioNode {
  public:
    OscillatorNode(unsigned sampleRate);
    void start();
    void stop();
    double getBufferSample();
    void setWaveform(std::unique_ptr<Waveform> wavefrom);
    void setMode(OscillatorMode mode);
    void setNote(unsigned note);
    void setFrequency(double frequency);
    void setGain(double gain);
    double getFrequency() const { return mFrequency; };
    unsigned getNote() const { return getNoteFromFrequency(mFrequency); };
    double getGain() const { return mGain; };

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(unsigned note);

  private:
    double mGain;
    double mFrequency;
    unsigned mSampleRate;
    bool mActive;

    std::unique_ptr<Waveform> mCustomWaveform;
    SineWave mSine;
    SawWave mSaw;
    SquareWave mSquare;

    OscillatorMode mMode;
    double mPhase;
    double mPhaseStep;
};

#endif
