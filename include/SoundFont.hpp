#ifndef SOUNDFONT_H
#define SOUNDFONT_H

#include "Instrument.hpp"

#define TSF_IMPLEMENTATION
#include "tsf.h"


namespace tsal {

class SoundFont : public Instrument {
  public:
    SoundFont(std::string filename);
    virtual double getOutput() override;
    virtual void noteOn(unsigned note, double velocity = 100.0) override;
    virtual void noteOff(unsigned note) override;
  private:
    tsf* mSoundFont;
};

}

#endif
