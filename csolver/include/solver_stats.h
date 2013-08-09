#ifndef SOLVER_STATS_H
#define SOLVER_STATS_H

#include "Timer.h"

class solver_stats_t {

private:

  Timer timer;
  double elapsed_time;
  long cycle_counter;

public:

  void start_timer();

  void stop_timer();

  void tick();

  void print();

};

#endif /* SOLVER_STATS_H */
