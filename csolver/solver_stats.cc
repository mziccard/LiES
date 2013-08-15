#include "solver_stats.h"
#include "utils.h"

void solver_stats_t::start_timer() {
  cycle_counter = 0;
  timer.start();
}

void solver_stats_t::stop_timer() {
  timer.stop();
  elapsed_time = timer.getElapsedTimeInMilliSec();
}

void solver_stats_t::tick() {
  cycle_counter++;
}

void solver_stats_t::print() {
  log(INFO_LEVEL, NEW_LINE, "[Stats]\t Inspected nodes: %d\n", cycle_counter);
  log(INFO_LEVEL, NEW_LINE, "[Stats]\t Execution time: %f\n", elapsed_time);
}
