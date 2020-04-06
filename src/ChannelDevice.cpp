#include "ChannelDevice.hpp"

namespace tsal {

/**
 * @brief Set the panning modifier or all the channels
 * 
 * @param channelCount 
 */
void ChannelDevice::setChannelPanning(unsigned channelCount) {
  switch (channelCount) {
    // mono channel
    case 1: {
      const double delta = (mPanning + 1)/2.0;
      mChannelPanning.resize(1);
      mChannelPanning[0] = delta;
      break;
    }
    // stereo channel
    case 2: {
      const double delta = (mPanning + 1) * M_PI/4.0;
      mChannelPanning.resize(2);
      mChannelPanning[0] = cos(delta);
      mChannelPanning[1] = sin(delta);
      break;
    }
  }
}

void ChannelDevice::setPanning(double panning) {
  mPanning = Util::checkParameterRange("Oscillator: Panning", panning, mPanningRange);
}

Util::ParameterRange<double> ChannelDevice::mPanningRange = std::make_pair(-1.0, 1.0);

}
