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
      ParameterManager(OscillatorParameters) {};
    Oscillator(std::vector<Parameter> parameters) :
      ParameterManager(OscillatorParameters) {
      addParameters(parameters);
    };
    static std::vector<Parameter> OscillatorParameters;
    enum Parameters {
                     OSCILLATOR_MODE = 0,
                     MODULATION_MODE,
                     MODULATION,
                     FREQUENCY,
                     PHASE_OFFSET,
    };
    enum ModulationMode {
                         NONE = 0,
                         MIX,
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
      WHITE_NOISE,
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
