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
                        { .name="Mode", .min=0.0, .max=2.0, .defaultValue=0.0 },
                        { .name="Frequency", .min=0.0, .max=1000.0, .defaultValue=1.0 },
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
      // Frequency parameter depends on sample rate
      parameterUpdate(frequency);
    }

    double getFrequency() const;
    unsigned getNote() const;

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(double note);

  protected:
    virtual void parameterUpdate(unsigned id) override;
  private:
    double polyBLEP(double t);
    
    double mPhase = 0.0;
    double mPhaseStep = 0.0;
    double mWaveFormValue = 0.0;

};

}
#endif
