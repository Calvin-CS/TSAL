#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#define _USE_MATH_DEFINES 
#include <cmath>
#define PI2 (M_PI * 2)

namespace tsal {

/** @class Util
 * @brief A utilities class
 *
 * Provides basic shared utility functions that programs and classes 
 * can make use of.
 */
class Util {
  public:
    enum TimeScale {
      SECOND = 1000000,
      MILLISECOND = 1000,
      MICROSECOND = 1,
    };
    static double ampToDb(double amplitude);
    static double dbToAmp(double db);
    static double volumeToDb(double volume);
    static double dbToVolume(double db);
    static void thread_sleep(unsigned duration, TimeScale scale = MILLISECOND);
    
    template <typename Item>
    using ParameterRange = std::pair<Item, Item>;
    
    template <typename Item>
    static Item checkParameterRange(const std::string& name, Item value, std::pair<Item, Item> range) {
      if (value < range.first || value > range.second) {
        std::cout << name << ": not in range["
                  << range.first << ", " 
                  << range.second
                  << "]" << std::endl;
      }
      return std::min(std::max(value, range.first), range.second);
    }
};


}

#endif
