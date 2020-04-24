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
 *
 * ParameterManager offers a interface for defining the parameters and their limits on an audio device
 */
class ParameterManager {
  public:
    struct Parameter {
        // The name the of the parameter
        std::string name; 
        // The minimum value that a user can assign
        double min;
        // The maximum value that a user can assign
        double max;
        // The default value that the parameter is initialized with
        double defaultValue;
        // The stored value
        double value;
        // Allows value to approach minimum without actually equaling minimum
        bool exclusiveMax = false;
        // Allows value to approach maximum without actually equaling maximum
        bool exclusiveMin = false;
        // Pointer to value
        double* connection = NULL;
    };
    ParameterManager() = default;
    ParameterManager(std::vector<Parameter> parameters) {
      mParameters.swap(parameters);
      for (auto& param : mParameters) {
        initializeParameter(param);
      }
    };

    std::string getParameterName(unsigned id) const { return mParameters[id].name; };
    Parameter& getParameterData(unsigned id) { return mParameters[id]; };
    double* getParameterPointer(unsigned id) { return &(mParameters[id].value); };
    template <typename T>
    T getParameter(unsigned id) { return static_cast<T>(getParameter(id)); };
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
    size_t getParameterCount() { return mParameters.size(); };
  protected:
    virtual void parameterUpdate(unsigned id) {};
    void addParameters(std::vector<Parameter> parameters) {
      for (unsigned i = 0; i < parameters.size(); i++) {
        mParameters.push_back(parameters[i]);
        initializeParameter(mParameters.back());
      }
    }
  private:
    void initializeParameter(Parameter& parameter) {
      parameter.value = parameter.defaultValue;
      if (parameter.exclusiveMax) {
        parameter.max -= EXCLUSIVE;
      }
      if (parameter.exclusiveMin) {
        parameter.min += EXCLUSIVE;
      }
    }
    double getConnectedParameter(unsigned id) {
      setParameter(id, *(mParameters[id].connection));
      return mParameters[id].value;
    };
    std::vector<Parameter> mParameters;
};

}
#endif
