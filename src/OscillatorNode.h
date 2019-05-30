#include <memory>
#include "AudioNode.h"
#include "RtAudio.h"
#include "SineWave.h"
#include "SawWave.h"
#include "SquareWave.h"

#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

/** \class OscillatorNode
 * \brief An audio node that generates sound from waveforms
 *  
 * OscillatorNode is a low level synthesizer that generates samples from
 * algorithmic waveforms. It supports saw, sine, and square waveforms, as well
 * as custom waveforms that can be created by the user.
 */
class OscillatorNode : public AudioNode {
  public:
    /**
     * \brief Modes for the oscillator 
     * 
     * Oscillator mode can be switched at anytime during execution
     */
    enum OscillatorMode {
      SAW,
      SINE,
      SQUARE,
      CUSTOM
    };

    OscillatorNode();

    /** 
     * \brief Start sampling the waveform 
     */
    void start();

    /** 
     * \brief Stop sampling the waveform 
     */
    void stop();

    double nextBufferSample();

    /** 
     * \brief Set a custom waveform for the oscillator
     * 
     * Given a Waveform class, the oscillator will automatically switch to CUSTOM mode and 
     * start sampling from the new waveform.
     * 
     * \param waveform a Waveform class that implements the getWaveformSample method
     */ 
    void setWaveform(Waveform waveform);

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
    static const double mPI2;
    double polyBLEP(double t);
    double mGain;
    double mFrequency;
    bool mActive;

    Waveform mCustomWaveform;
    SineWave mSine;
    SawWave mSaw;
    SquareWave mSquare;

    OscillatorMode mMode;
    double mPhase;
    double mPhaseStep;
};

#endif
