#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "OutputDevice.hpp"
#include "ParameterManager.hpp"

namespace tsal {

/** @class Oscillator
 * @brief A device that generates sound from a waveform
 *  
 * Oscillator is a low level synthesizer that generates samples from
 * algorithmic waveforms. It supports saw, sine, and square waveforms
 */
class Oscillator : public OutputDevice, public ParameterManager {
  public:
    Oscillator() :
      ParameterManager({
                        { .name="Mode", .max=0.0, .min=2.0, .defaultValue=0.0 },
                        { .name="Frequency", .max=0.0, .min=5.0, .defaultValue=1.0 },
        }){
    }
    enum Parameters {
                     mode = 0,
                     frequency,
    };
    /**
     * @brief Modes for the oscillator 
     * 
     * Oscillator mode can be switched at anytime during execution
     */
    enum OscillatorMode {
      SINE = 0,
      SAW,
      SQUARE
    };

    double getSample();
    void setMode(OscillatorMode mode);
    void setNote(double note);
    void setFrequency(double frequency);
    virtual void updateContext(const Context &context) override {
      OutputDevice::updateContext(context);
      setFrequency(mFrequency);
    }

    double getFrequency() const;
    unsigned getNote() const;

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(double note);

  private:
    double polyBLEP(double t);
    double mFrequency = 0.0;
    
    OscillatorMode mMode = SINE;
    double mPhase = 0.0;
    double mPhaseStep = 0.0;
    double mWaveFormValue = 0.0;

    static Util::ParameterRange<double> mNoteRange;
    static Util::ParameterRange<double> mFrequencyRange;
};

}
#endif
