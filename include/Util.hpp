#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#define _USE_MATH_DEFINES 
#include <cmath>

namespace tsal {

// I want to figure this thing out
template <typename Item>
using ParameterRange = std::pair<Item, Item>;

template <typename Item>
Item checkParameterRange(const std::string& name, Item value, std::pair<Item, Item> range) {
  if (value < range.first || value > range.second) {
    std::cout << name << ": not in range["
              << range.first << ", " 
              << range.second
              << "]" << std::endl;
  }
  return std::min(std::max(value, range.first), range.second);
}

double ampToDb(double amplitude);
double dbToAmp(double db);

}

#endif
