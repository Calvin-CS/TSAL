#ifndef PANNING_H
#define PANNING_H

#include "OutputDevice.hpp"
#include "ParameterManager.hpp"
#include <vector>

namespace tsal {

/** @class 
 * @brief 
 */
class Panning {
  public:
    static ParameterManager::Parameter PanningParameter;
    double getPanningChannel(unsigned channel) const { return mChannelPanning[channel]; };
    void setPanning(double panning) { mPanning = panning; };
    void setChannelPanning(unsigned channelCount);
  protected:
    double mPanning = 0.0;
    std::vector<double> mChannelPanning;
  private:
    static double panningConstant;
};

}

#endif
