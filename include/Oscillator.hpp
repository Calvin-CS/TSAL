#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

#include "Instrument.hpp"
#include "Envelope.hpp"
#include "Mixer.hpp"

namespace tsal {

/** @class Oscillator
 * @brief A device that generates sound from a waveform
 *  
 * Oscillator is a low level synthesizer that generates samples from
 * algorithmic waveforms. It supports saw, sine, and square waveforms
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
      SQUARE
    };

    Oscillator();
    double getOutput() override;

    void start();
    void stop();
    void playNote(unsigned note, double velocity);

    void setMode(OscillatorMode mode);
    void setNote(unsigned note);
    void setFrequency(double frequency);
    void setVelocity(double velocity);
    void setGain(double gain);

    double getFrequency() const;
    double getGain() const;
    unsigned getNote() const;

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(unsigned note);

  private:
    double polyBLEP(double t);
    double mFrequency;
    double mGainAmp;
    double mVelocity;
    
    OscillatorMode mMode;
    double mPhase = 0.0;
    double mPhaseStep = 0.0;
    double mWaveFormValue = 0.0;

    static ParameterRange<unsigned> mNoteRange;
    static ParameterRange<double> mVelocityRange;
    static ParameterRange<double> mFrequencyRange;
    static ParameterRange<double> mGainRange;
};

}
#endif
