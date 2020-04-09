#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H

#include <sched.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#define EXCLUSIVE 0.0001

namespace tsal {

/** @class ParameterManager
 * @brief An interface for defining and modifing parameters on a device
 */
class ParameterManager {
  public:
    struct Parameter {
        std::string name;
        double min;
        double max;
        double defaultValue;
        double value;
        bool exclusiveMax = false;
        bool exclusiveMin  = false;
    };
    ParameterManager(std::vector<Parameter>&& parameters) {
      mParameters.swap(parameters);
      for (auto& param : mParameters) {
        param.value = param.defaultValue;
        if (param.exclusiveMax) {
          param.max -= EXCLUSIVE;
        }
        if (param.exclusiveMin) {
          param.min += EXCLUSIVE;
        }
      }
    };

    std::string getParameterName(unsigned id) const { return mParameters[id].name; };
    int getParameterInt(unsigned id) const { return std::round(mParameters[id].value); };
    double getParameter(unsigned id) const { return mParameters[id].value; };
    void setParameter(unsigned id, double value) {
      auto& param = mParameters[id];
      param.value = std::min(std::max(value, param.min), param.max);
      parameterUpdate(id);
    }
  protected:
    virtual void parameterUpdate(unsigned id) {};
  private:
    std::vector<Parameter> mParameters;
};

}
#endif
