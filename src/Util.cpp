#include "Util.hpp"

namespace tsal {

double ampToDb(double amplitude) {
  return 20.0 * std::log10(amplitude) / M_LN10;
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
