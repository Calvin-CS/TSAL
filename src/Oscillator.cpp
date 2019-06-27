#include "Oscillator.hpp"
#include "Util.hpp"
#include "MidiNotes.hpp"
#include <iostream>

namespace tsal {

Oscillator::Oscillator() {
  setMode(SINE);
  setGain(-10.0);
  setNote(C4);
  setVelocity(127.0);
}

void Oscillator::start() {
  //envelope.start();
}

void Oscillator::stop() {
  //envelope.stop();
}

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

  return mWaveFormValue * SCALE * mGainAmp * (mVelocity / 127.0);
}

/**
 * @brief Get the note from a corresponding frequency
 * 
 * @param frequency 
 * @return unsigned 
 */
unsigned Oscillator::getNoteFromFrequency(double frequency) {
  return (12/log(2)) * log(frequency/27.5) + 21;
}

/**
 * @brief Get the frequency from a corresponding note
 * 
 * @param note 
 * @return double 
 */
double Oscillator::getFrequencyFromNote(unsigned note) {
  return 27.5 * pow(2.0, (note - 21) / 12.0);
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
 * @brief Play a note with a velocity
 * 
 * @param note 
 * @param velocity
 */
void Oscillator::playNote(unsigned note, double velocity) {
  setFrequency(getFrequencyFromNote(note));
  setVelocity(velocity);
  start();
}

/**
 * @brief Set the note 
 * 
 * @param note (midi format)
 */
void Oscillator::setNote(unsigned note) {
  setFrequency(getFrequencyFromNote(checkParameterRange("Oscillator: Note", note, mNoteRange)));
}

/**
 * @brief Set the frequncy
 * 
 * @param frequency 
 */
void Oscillator::setFrequency(double frequency) {
  mFrequency = checkParameterRange("Oscillator: Frequency", frequency, mFrequencyRange);
  mPhaseStep = mFrequency * PI2 / ((double) Mixer::getSampleRate());
}

/**
 * @brief Set the velocity
 * 
 * @param velocity
 */
void Oscillator::setVelocity(double velocity) {
  mVelocity = checkParameterRange("Oscillator: Velocity", velocity, mVelocityRange);
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
 * @brief Set the gain
 * 
 * @param gain 
 */
void Oscillator::setGain(double gain) {
  mGainAmp = dbToAmp(checkParameterRange("Oscillator: Gain", gain, mGainRange));
}

/**
 * @brief Get the gain
 * 
 * @return double 
 */
double Oscillator::getGain() const {
  return ampToDb(mGainAmp);
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

ParameterRange<unsigned> Oscillator::mNoteRange = std::make_pair(21, 108);
ParameterRange<double> Oscillator::mVelocityRange = std::make_pair(0.0, 127.0);
ParameterRange<double> Oscillator::mFrequencyRange = std::make_pair(27.5, 4186.0);
ParameterRange<double> Oscillator::mGainRange = std::make_pair(-50.0, 50.0);

}
