#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H

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
        bool exclusiveMin = false;
        double* connection = NULL;
    };
    ParameterManager() = default;
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
    Parameter& getParameterData(unsigned id) { return mParameters[id]; };
    double* getParameterPointer(unsigned id) { return &(mParameters[id].value); };
    int getParameterInt(unsigned id) { return std::round(getParameter(id)); };
    double getParameter(unsigned id) {
      auto& param = mParameters[id];
      return param.connection == NULL ? mParameters[id].value : getConnectedParameter(id);
    };
    void setParameter(unsigned id, double value) {
      auto& param = mParameters[id];
      param.value = std::min(std::max(value, param.min), param.max);
      parameterUpdate(id);
    }
    void connectParameter(unsigned id, double* connection) {
      mParameters[id].connection = connection;
    }
    void disconnectParameter(unsigned id) {
      mParameters[id].connection = NULL;
    }
    void disconnectParameters() {
      for (unsigned i = 0; i < mParameters.size(); i++) {
        disconnectParameter(i);
      }
    }
  protected:
    virtual void parameterUpdate(unsigned id) {};
  private:
    
    double getConnectedParameter(unsigned id) {
      setParameter(id, *(mParameters[id].connection));
      return mParameters[id].value;
    };
    std::vector<Parameter> mParameters;
};

}
#endif
