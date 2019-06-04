#include "Instrument.h"
#include "RtAudio.h"
#include "SineWave.h"
#include "SawWave.h"
#include "SquareWave.h"

#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

namespace tsal {

/** @class Oscillator
 * @brief An audio node that generates sound from waveforms
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

    /** 
     * @brief Set a custom waveform for the oscillator
     * 
     * Given a Waveform class, the oscillator will automatically switch to CUSTOM mode and 
     * start sampling from the new waveform.
     * 
     * @param waveform a Waveform class that implements the getWaveformSample method
     */ 
    void setWaveform(Waveform waveform);

    /**
     * @brief Set the mode
     * 
     * @param mode 
     */
    void setMode(OscillatorMode mode);

    /**
     * @brief Set the note 
     * 
     * @param note (midi format)
     */
    void setNote(unsigned note);

    /**
     * @brief Set the frequncy
     * 
     * @param frequency 
     */
    void setFrequency(double frequency);

    /**
     * @brief Set the gain
     * 
     * @param gain 
     */
    void setGain(double gain);

    /**
     * @brief Get the frequency
     * 
     * @return double 
     */
    double getFrequency() const { return mFrequency; };

    /**
     * @brief Get the note
     * 
     * @return unsigned (midi)
     */
    unsigned getNote() const { return getNoteFromFrequency(mFrequency); };

    /**
     * @brief Get the gain
     * 
     * @return double 
     */
    double getGain() const { return mGain; };

    /**
     * @brief Get the note from a corresponding frequency
     * 
     * @param frequency 
     * @return unsigned 
     */
    static unsigned getNoteFromFrequency(double frequency);

    /**
     * @brief Get the frequency from a corresponding note
     * 
     * @param note 
     * @return double 
     */
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
};

}
#endif
