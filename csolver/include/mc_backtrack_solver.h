#ifndef MC_BACKTRACK_SOLVER_H
#define MC_BACKTRACK_SOLVER_H

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csp.h"
#include "utils.h"
#include "backtrack_solver.h"

using namespace std;

/**
 * Backtrack solver implementing the most constrained
 * variable heuristic: selects to be assigned always the most
 * constrained variable. That is, the variable which is involved
 * in the biggest number of constraints
 **/

class mc_backtrack_solver_t : public backtrack_solver_t {
  private: 
    // Variables ordered by number of constraints
    int* mc_ordered_variables;

  protected:

    void preprocess();

  public:
    mc_backtrack_solver_t(csp_t mcsp);

    virtual bool solve(int* solutions);

    virtual bool solve_rec(int index, int* solutions);
};

#endif /*MC_BACKTRACK_SOLVER_H*/
