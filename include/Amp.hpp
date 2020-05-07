#ifndef AMP_H
#define AMP_H

#include "Util.hpp"
#include "ParameterManager.hpp"

namespace tsal {

class Amp {
  public:
    static ParameterManager::Parameter AmpParameterVolume;
    static ParameterManager::Parameter AmpParameterGain;
    inline double getAmp() const { return mAmp; };
    void setGain(double gain) {
      mAmp = Util::dbToAmp(gain);
    };
    void setVolume(double volume){
      mAmp = Util::dbToAmp(Util::volumeToDb(volume));
    }; 
  private:
    double mAmp = 0.5;
};

}
#endif 
