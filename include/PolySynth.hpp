#ifndef POLYSYNTH_H
#define POLYSYNTH_H

#include "ParameterManager.hpp"
#include "Synth.hpp"
#include "Oscillator.hpp"
#include "Instrument.hpp"
#include "RouteDevice.hpp"

#define NUM_VOICES 20

namespace tsal {

/** @class PolySynth
 * @brief A polyphonic synthesizer
 *
 * PolySynth uses multiple Synths to create a polyphonic 
 * synthesizer that can handle multiple notes being played
 * at the same time
 */
class PolySynth : public Instrument, public ParameterManager {
  public:
    PolySynth(PolySynth&& other) noexcept :
      mVoices(std::move(other.mVoices)) {
      for (unsigned i = 0; i < mVoices.size(); i++) {
        mVoices[i].stop(0.0);
      }
      updateContext(other.mContext);
    };
    PolySynth() :
      ParameterManager({
               { .name="Osc1Mode", .min=0.0, .max=2.0, .defaultValue=1.0 },
               { .name="Osc2Mode", .min=0.0, .max=2.0, .defaultValue=1.0 },
               { .name="ModulationMode", .min=0.0, .max=2.0, .defaultValue=0.0 },
        }),
      mVoices(NUM_VOICES, Voice())
    {
      for (auto& voice : mVoices) {
        voice.setActive(false);
        voice.mOsc1.connectParameter(Oscillator::OSCILLATOR_MODE, getParameterPointer(OSC1_MODE));
        voice.mOsc2.connectParameter(Oscillator::OSCILLATOR_MODE, getParameterPointer(OSC2_MODE));
        voice.mOsc1.connectParameter(Oscillator::MODULATION_MODE, getParameterPointer(MODULATION_MODE));
      }
    };
    enum Parameters {
                     OSC1_MODE = 0,
                     OSC2_MODE,
                     MODULATION_MODE,
                     ENV_ATTACK,
                     ENV_DECAY,
                     ENV_SUSTAIN,
                     ENV_RELEASE,
    };
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void play(double note, double velocity = 100.0) override;
    void stop(double note) override;
    void setMode(Oscillator::OscillatorMode mode);
    PolySynth& operator=(const PolySynth& synth);
    virtual void updateContext(const Context& context) override;
  protected:
    virtual void parameterUpdate(unsigned id) override;
  private:
    class Voice : public Instrument {
      public:
        Voice() {
          mEnvelope.setActive();
          mFilter.setMode(Filter::BANDPASS);
          mFilter.setCutoff(0.1);
        }
        double getSample();
        void play(double note, double velocity) override;
        void stop(double note = MidiNote::A0) override;
        virtual void updateContext(const Context& context) override; 
        double getNote() { return mOsc1.getNote(); };
        
        Oscillator mOsc1;
        Oscillator mOsc2;
        Filter mFilter;
        Envelope mEnvelope;

        Oscillator::ModulationMode mModulationMode = Oscillator::MIX;
        double mVelocity = 100.0;
        unsigned mNote = 0.0;
    };
    Voice* getInactiveVoice();
    std::vector<Voice> mVoices;
};
  
}

#endif
