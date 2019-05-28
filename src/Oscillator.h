#include <memory>
#include "RtAudio.h"
#include "SineWave.h"
#include "SawWave.h"
#include "SquareWave.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

enum OscillatorMode {
  SAW,
  SINE,
  SQUARE,
  CUSTOM
};

class Oscillator {
  public:
    Oscillator();
    Oscillator(unsigned channels, unsigned sampleRate);
    ~Oscillator();
    void start();
    void stop();
    double getBufferSample();
    void setWaveform(std::unique_ptr<Waveform> wavefrom);
    void setMode(OscillatorMode mode);
    void setNote(unsigned note);
    void setFrequency(double frequency);
    void setGain(double gain);
    double getFrequency() const { return mFrequency; };
    double getGain() const { return mGain; };

    static double getFrequencyFromNote(unsigned note) {
      return 27.5 * pow(2.0, (note - 21) / 12.0);
    };

  private:
    void initStream();
    RtAudio mRtAudio;
    double mGain;
    double mFrequency;
    double mSampleRate;
    double mChannels;
    
    std::unique_ptr<Waveform> mCustomWaveform;
    SineWave mSine;
    SawWave mSaw;
    SquareWave mSquare;

    OscillatorMode mMode;
    double mPhase;
    double mPhaseStep;
};

#endif
