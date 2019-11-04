#include "Oscillator.hpp"
#include "Util.hpp"
#include "MidiNotes.hpp"
#include <iostream>

namespace tsal {

// Helpful implementation of ployBLEP to reduce aliasing
// http://metafunction.co.uk/all-about-digital-oscillators-part-2-blits-bleps/
double Oscillator::getOutput() {
  // If not active, move value to 0
  if (!mActive) {
    return 0.0;
  } 
  double t = mPhase / PI2;

  switch (mMode) {
    case SINE:
      mWaveFormValue = sin(mPhase);
      break;
    case SAW:
      mWaveFormValue = (2.0 * mPhase / PI2) - 1.0;
      mWaveFormValue -= polyBLEP(t); // Layer output of Poly BLEP on top
      break;
    case SQUARE:
      mWaveFormValue = mPhase < M_PI ? 1 : -1;
      mWaveFormValue += polyBLEP(t); // Layer output of Poly BLEP on top (flip)
      mWaveFormValue -= polyBLEP(fmod(t + 0.5, 1.0)); // Layer output of Poly BLEP on top (flop)
      break;
  }

  mPhase += mPhaseStep;  
  while (mPhase >= PI2)
    mPhase -= PI2;

  return mWaveFormValue * mAmp;
}

void Oscillator::getOutput(std::vector<float>& buffer, unsigned long frameCount, unsigned channelCount) {
  if (mActive) {
    for (unsigned long i = 0; i < frameCount; i += channelCount) {
      for (unsigned j = 0; j < channelCount; j++) {
        buffer[i + j] = getOutput();
      }
    }
  }
}
/**
 * @brief Get the note from a corresponding frequency
 * 
 * @param frequency 
 * @return unsigned 
 */
unsigned Oscillator::getNoteFromFrequency(double frequency) {
  return (12/log(2)) * std::log(frequency/27.5) + 21;
}

/**
 * @brief Get the frequency from a corresponding note
 * 
 * @param note 
 * @return double 
 */
double Oscillator::getFrequencyFromNote(double note) {
  return 27.5 * pow(2.0, (note - 21.0) / 12.0);
}

double Oscillator::polyBLEP(double t)
{
  double dt = mPhaseStep / PI2;

  // t-t^2/2 +1/2
  // 0 < t <= 1
  // discontinuities between 0 & 1
  if (t < dt) {
   t /= dt;
   return t + t - t * t - 1.0;
  }

  // t^2/2 +t +1/2
  // -1 <= t <= 0
  // discontinuities between -1 & 0
  else if (t > 1.0 - dt) {
   t = (t - 1.0) / dt;
   return t * t + t + t + 1.0;
  }

  // no discontinuities 
  // 0 otherwise
  else return 0.0;
}

/**
 * @brief Set the note 
 * 
 * @param note (midi format)
 */
void Oscillator::setNote(double note) {
  setFrequency(getFrequencyFromNote(Util::checkParameterRange("Oscillator: Note", note, mNoteRange)));
}

/**
 * @brief Set the frequncy
 * 
 * @param frequency 
 */
void Oscillator::setFrequency(double frequency) {
  mFrequency = Util::checkParameterRange("Oscillator: Frequency", frequency, mFrequencyRange);
  mPhaseStep = mFrequency * PI2 / mMixer->getSampleRate();
}

/**
 * @brief Set the mode
 *  
 * @param mode 
 */
void Oscillator::setMode(OscillatorMode mode) {
  mMode = mode;
}

/**
 * @brief Get the frequency
 * 
 * @return double 
 */
double Oscillator::getFrequency() const {
  return mFrequency;
}

/**
 * @brief Get the note
 * 
 * @return unsigned (midi)
 */
unsigned Oscillator::getNote() const {
  return getNoteFromFrequency(mFrequency);
}

Util::ParameterRange<double> Oscillator::mNoteRange = std::make_pair(21.0, 108.0);
Util::ParameterRange<double> Oscillator::mFrequencyRange = std::make_pair(27.5, 4186.0);

}
