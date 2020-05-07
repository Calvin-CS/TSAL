#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "ChannelDevice.hpp"
#include "ParameterManager.hpp"
#include "Sequencer.hpp"
#include "Panning.hpp"
#include "Amp.hpp"

namespace tsal {

/** @class Instrument
 * @brief An abstract class to provide expected behaviors of instruments
 * 
 */
class Instrument : public ChannelDevice, public ParameterManager {
  public:
    Instrument() :
      ParameterManager(InstrumentParameters) {};
    Instrument(std::vector<Parameter> parameters) :
      ParameterManager(InstrumentParameters) {
      addParameters(parameters);
    };
    static std::vector<Parameter> InstrumentParameters;
    enum Parameters {
                     VOLUME = 0,
                     PANNING,
    };
    virtual void play(double note, double velocity = 100.0) = 0;
    virtual void stop(double note) = 0;
    virtual ~Instrument();
    virtual void setParentChannel(Channel* channel) override;
  protected:
    virtual void parameterUpdate(unsigned id) override; 
    Panning mPanning;
    Amp mAmp;
};

}

#endif
