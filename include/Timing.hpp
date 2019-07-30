#ifndef TIMING_H
#define TIMING_H

namespace tsal {

class Timing {
  public:
    enum TimeScale {
      SECOND = 1000000,
      MILLISECOND = 1000,
      MICROSECOND = 1,
    };
    enum NoteScale {
      TICK = 0,
      EIGHTH = 8,
      QUATER = 4,
      HALF = 2,
      WHOLE = 1,
    };
};

} // namespace tsal

#endif
