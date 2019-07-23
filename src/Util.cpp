#include "Util.hpp"
#include <chrono>
#include <thread>

namespace tsal {

void Util::thread_sleep(unsigned duration, const TimeScale scale) {
  std::this_thread::sleep_for(duration * std::chrono::microseconds(scale));
}

double Util::ampToDb(double amplitude) {
  return 20.0 * std::log(amplitude) / M_LN10;
}

double Util::dbToAmp(double db) {
  return std::pow(10.0, db / 20.0);
}

double Util::volumeToDb(double volume) {
  return 33.22 * std::log10(volume);
}

double Util::dbToVolume(double db) {
  return std::pow(10.0, db / 33.22);
}

}
