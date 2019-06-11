#include "Instrument.h"
#include "Envelope.h"
#include "SineWave.h"
#include "SawWave.h"
#include "SquareWave.h"
#include "Mixer.h"

#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

namespace tsal {

/** @class Oscillator
 * @brief A device that generates sound from a waveform
 *  
 * Oscillator is a low level synthesizer that generates samples from
 * algorithmic waveforms. It supports saw, sine, and square waveforms, as well
 * as custom waveforms that can be created by the user.
 */
class Oscillator : public Instrument {
  public:
    /**
     * @brief Modes for the oscillator 
     * 
     * Oscillator mode can be switched at anytime during execution
     */
    enum OscillatorMode {
      SAW,
      SINE,
      SQUARE,
      CUSTOM
    };

    Oscillator();
    double getOutput() override;

    void start();
    void stop();
    
    void setWaveform(Waveform waveform);
    void setMode(OscillatorMode mode);
    void setNote(unsigned note);
    void setFrequency(double frequency);
    void setGain(double gain);

    double getFrequency() const;
    unsigned getNote() const;
    double getGain() const;

    static unsigned getNoteFromFrequency(double frequency);

    static double getFrequencyFromNote(unsigned note);

  private:
    static const double mPI2;
    double polyBLEP(double t);
    double mGain;
    double mFrequency;

    Waveform mCustomWaveform;
    SineWave mSine;
    SawWave mSaw;
    SquareWave mSquare;

    OscillatorMode mMode;
    double mPhase;
    double mPhaseStep;
    double mWaveFormValue = 0.0;

    // Just testing
    Envelope envelope;
};

}
#endif
