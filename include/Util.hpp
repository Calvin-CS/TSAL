#ifndef UTIL_H
#define UTIL_H

#include "Timing.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#define _USE_MATH_DEFINES
#include <cmath>
#define PI2 (M_PI * 2)

#include <chrono>
#include <thread>

namespace tsal {

/** @class Util
 * @brief A utilities class
 *
 * Provides basic shared utility functions that programs and classes
 * can make use of.
 */
class Util {
  public:
    static double random() { return mDist(mGen); };
    static double ampToDb(double amplitude);
    static double dbToAmp(double db);
    static double volumeToDb(double volume);
    static double dbToVolume(double db);
    static void thread_sleep(unsigned duration, Timing::TimeScale scale = Timing::MILLISECOND);

    template <typename T>
    using ParameterRange = std::pair<T, T>;

    template <typename T>
    static T checkParameterRange(const std::string& name, T value, ParameterRange<T> range) {
      if (value < range.first || value > range.second) {
        std::cout << name << ": not in range["
                  << range.first << ", "
                  << range.second
                  << "]" << std::endl;
      }
      return std::min(std::max(value, range.first), range.second);
    }

    /**
     * @brief Forces a hidden floor value on the range 
     * 
     * Lets the user set expected values without causing divide by 0 or other arithmetic errors
     */
    template <typename T>
    static T checkParameterRangeHiddenFloor(const std::string& name, T value, ParameterRange<T> range, T floor) {
      return std::max(Util::checkParameterRange(name, value, range), floor);
    }

    /**
     * @brief Forces a hidden ceiling value on the range 
     * 
     * Lets the user set expected values without causing divide by 0 or other arithmetic errors
     */
    template <typename T>
    static T checkParameterRangeHiddenCeiling(const std::string& name, T value, ParameterRange<T> range, T ceiling) {
      return std::min(Util::checkParameterRange(name, value, range), ceiling);
    }
    static std::mt19937 mGen;
    static std::uniform_real_distribution<> mDist;
};


}

#endif
