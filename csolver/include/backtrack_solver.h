#ifndef BACKTRACK_SOLVER_H
#define BACKTRACK_SOLVER_H

#include "csp.h"
#include "solver_stats.h"
#include "solver.h"

using namespace std;

class backtrack_solver_t: public solver_t {
  protected:

    csp_t           csp;
    int*            assigned_variables; 
    solver_stats_t  stats; 


  public:
	
    backtrack_solver_t(csp_t mcsp);

    virtual bool is_consistent(int* solutions);

    virtual bool solve(int* solutions);

    virtual bool solve_rec(int first, int* solutions);

};

#endif /* BACKTRACK_SOLVER_H */
