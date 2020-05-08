#include "PolySynth.hpp"
#include "Envelope.hpp"
#include "Oscillator.hpp"

namespace tsal {

std::vector<ParameterManager::Parameter> PolySynth::PolySynthParameters
({
  { .name="Osc1 Mode", .min=0.0, .max=3.0, .defaultValue=0.0 },
  { .name="Osc2 Mode", .min=0.0, .max=3.0, .defaultValue=0.0 },
  { .name="Osc2 Offset", .min=0.0, .max=1.0, .defaultValue=0.0},
  { .name="Modulation Mode", .min=0.0, .max=3.0, .defaultValue=0.0 },
  { .name="Attack", .min=0.0, .max=100.0, .defaultValue=0.0, .exclusiveMin=true },
  { .name="Decay", .min=0.0, .max=100.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="Sustain", .min=0.0, .max=1.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="Release", .min=0.0, .max=100.0, .defaultValue=2.0, .exclusiveMin=true },
  { .name="LFO Active", .min=0.0, .max=1.0, .defaultValue=0.0 },
  { .name="LFO Mode", .min=0.0, .max=3.0, .defaultValue=0.0 },
  { .name="LFO Frequency", .min=0.0, .max=15000.0, .defaultValue=1.0 },
  { .name="LFO Attack", .min=0.0, .max=100.0, .defaultValue=0.0, .exclusiveMin=true },
  { .name="LFO Decay", .min=0.0, .max=100.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="LFO Sustain", .min=0.0, .max=1.0, .defaultValue=0.5, .exclusiveMin=true },
  { .name="LFO Release", .min=0.0, .max=100.0, .defaultValue=2.0, .exclusiveMin=true },
});

void PolySynth::getOutput(AudioBuffer<float> &buffer) {
  if (!mActive) {
    return;
  }
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();

  mPanning.setChannelPanning(channels);

  for (unsigned long i = 0; i < frames; i++) {
    // Get the collective output of the voices
    double lfo = ((getParameter(LFO_ACTIVE) > 0.5 ? mLFO.getSample() : 1.0) + 1) / 2;
    double output = 0.0;
    double activeVoices = 0.0;
    for (size_t k = 0; k < mVoices.size(); k++) {
      if (mVoices[k].isActive()) {
        output += mVoices[k].getSample(lfo);
        ++activeVoices;
      }
    }
    // output += mVoices[0].getSample();
    // Scale the output by the number of active voices 
    // output = activeVoices > 0 ? output / activeVoices : output;

    for (unsigned j = 0; j < channels; j++) {
      buffer[i * channels + j] = output * mAmp.getAmp() * mPanning.getPanningChannel(j) * lfo; 
    }
  }
}

void PolySynth::updateContext(const Context& context) {
  OutputDevice::updateContext(context); 
  for (auto& voice : mVoices) {
    voice.updateContext(context);
  }
  mLFO.updateContext(context);
}

/* @brief Play a note with velocity
 *
 * @param note
 * @param velocity
 */
void PolySynth::play(double note, double velocity) {
  Voice* voice = getInactiveVoice();
  if (voice == nullptr) {
    voice = &mVoices[0]; 
    voice->stop();
  }
  voice->play(note, velocity);
}

/* @brief Stop playing a note
 *
 * @param note
 */
void PolySynth::stop(double note) {
  for (auto& voice : mVoices) {
    if (voice.getNote() == note) {
      voice.stop();
    }
  }
}

/* @brief Set the mode of the underlying synths
 *
 * @param mode
 */
void PolySynth::setMode(Oscillator::OscillatorMode mode) {
  for (unsigned i = 0; i < mVoices.size(); i++) {
  }
}

PolySynth::Voice* PolySynth::getInactiveVoice() {
  static unsigned i = 0;
  // Whenever a note is pressed, an inactive voice needs to be found an played
  // If all the voices are active, a nullptr is returned
  // Voice* voice = nullptr;
  // for (unsigned i = 0; i < mVoices.size(); i++) {
  //   if (!mVoices[i].isActive()) {
  //     mVoices[i].setActive();
  //     voice = &mVoices[i];
  //     break;
  //   }
  // }
  return &mVoices[i++ % mVoices.size()];
}

double PolySynth::Voice::getSample(double lfo) {
  mOsc1.setParameter(Oscillator::MODULATION, mOsc2.getSample());
  return lfo * mLFOEnvelope.getSample() * mFilter.process(mOsc1.getSample() *
                         (mVelocity / 120.0) *
                         mEnvelope.getSample());
}

void PolySynth::Voice::play(double note, double velocity) {
  mNote = note;
  setActive();
  mOsc1.setActive();
  mOsc2.setActive();
  mEnvelope.start();
  mLFOEnvelope.start();
  mVelocity = velocity; 
  mOsc1.setNote(note);
  mOsc2.setNote(note);
}

void PolySynth::Voice::stop(double note) {
  (void)note;
  if (mEnvelope.isActive()) {
    mEnvelope.stop();
    // mLFOEnvelope.stop();
  } else {
    // mOsc1.setActive(false);
    // mOsc2.setActive(false);
  }
}

void PolySynth::Voice::updateContext(const Context& context) {
    mOsc1.updateContext(context);
    mOsc2.updateContext(context);
    mEnvelope.updateContext(context);
    mLFOEnvelope.updateContext(context);
}

}
