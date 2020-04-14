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
                        { .name="OscillatorMode", .min=0.0, .max=2.0, .defaultValue=0.0 },
                        { .name="ModulationMode", .min=0.0, .max=2.0, .defaultValue=0.0 },
                        { .name="Modulation", .min=-1.0, .max=1.0, .defaultValue=0.0 },
                        { .name="Frequency", .min=0.0, .max=1000.0, .defaultValue=1.0 },
        }){
    };
    enum Parameters {
                     OSCILLATOR_MODE = 0,
                     MODULATION_MODE,
                     MODULATION,
                     FREQUENCY,
    };
    enum ModulationMode {
                     MIX = 0,
                     AM, // Amplitude modulation
                     PM, // Phaser modulation
    };
    /**
     * @brief Modes for the oscillator 
     * 
     * Oscillator mode can be switched at anytime during execution
     */
    enum OscillatorMode {
      SINE = 0,
      SAW,
      SQUARE,
    };

    double getSample();
    void setMode(OscillatorMode mode);
    void setNote(double note);
    void setFrequency(double frequency);
    virtual void updateContext(const Context &context) override {
      OutputDevice::updateContext(context);
      // Frequency parameter depends on sample rate
      parameterUpdate(FREQUENCY);
    }

    double getFrequency();
    unsigned getNote();

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(double note);

  protected:
    virtual void parameterUpdate(unsigned id) override;
  private:
    double polyBLEP(double t);
    

    double mPhase = 0.0;
    double mPhaseStep = 0.0;

};

}
#endif
