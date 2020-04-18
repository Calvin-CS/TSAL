#include "Oscillator.hpp"
#include "Util.hpp"
#include "MidiNotes.hpp"
#include <iostream>

namespace tsal {

// Helpful implementation of ployBLEP to reduce aliasing
// http://metafunction.co.uk/all-about-digital-oscillators-part-2-blits-bleps/
double Oscillator::getSample() {
  const double t = mPhase / PI2;
  const double modulation = getParameter(MODULATION);
  const ModulationMode modulationMode = (ModulationMode) getParameterInt(MODULATION_MODE);
  double phase = mPhase + (getParameter(PHASE_OFFSET) * PI2);
  double output = 0.0;
  
  if (modulationMode == PM) {
    phase += modulation;
  }

  switch (getParameterInt(OSCILLATOR_MODE)) {
    case SINE:
      output = sin(phase);
      break;
    case SAW:
      output = (2.0 * phase / PI2) - 1.0;
      output -= polyBLEP(t); // Layer output of Poly BLEP on top
      break;
    case SQUARE:
      output = phase < M_PI ? 1 : -1;
      output += polyBLEP(t); // Layer output of Poly BLEP on top (flip)
      output -= polyBLEP(fmod(t + 0.5, 1.0)); // Layer output of Poly BLEP on top (flop)
      break;
    case WHITE_NOISE:
      output = Util::random() * 2 - 1;
      break;
  }

  if (modulationMode == AM) {
    output *= modulation;
  } else if (modulationMode == MIX) {
    output = (output + modulation) / 2.0;
  }
  

  mPhase += mPhaseStep;  
  while (mPhase >= PI2)
    mPhase -= PI2;

  return output * mAmp;
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
  setParameter(FREQUENCY, getFrequencyFromNote(note));
}

/**
 * @brief Set the frequncy
 * 
 * @param frequency 
 */
void Oscillator::setFrequency(double frequency) {
  setParameter(FREQUENCY, frequency);
}

/**
 * @brief Set the mode
 *  
 * @param mode 
 */
void Oscillator::setMode(OscillatorMode mode) {
  setParameter(OSCILLATOR_MODE, mode);
}

/**
 * @brief Get the frequency
 * 
 * @return double 
 */
double Oscillator::getFrequency() {
  return getParameter(FREQUENCY);
}

/**
 * @brief Get the note
 * 
 * @return unsigned (midi)
 */
unsigned Oscillator::getNote() {
  return getNoteFromFrequency(getParameter(FREQUENCY));
}

void Oscillator::parameterUpdate(unsigned id) {
  switch (id) {
  case FREQUENCY:
    mPhaseStep = getParameter(FREQUENCY) * PI2 / mContext.getSampleRate();
    break;
  }
}

}
