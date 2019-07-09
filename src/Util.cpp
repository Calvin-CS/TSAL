#include "Util.hpp"
#include <chrono>
#include <thread>

namespace tsal {

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

double ampToDb(double amplitude) {
  return 20.0 * std::log(amplitude) / M_LN10;
}

double dbToAmp(double db) {
  return std::pow(10.0, db / 20.0);
}

double volumeToDb(double volume) {
  return 33.22 * std::log10(volume);
}

double dbToVolume(double db) {
  return std::pow(10.0, db / 33.22);
}

}
