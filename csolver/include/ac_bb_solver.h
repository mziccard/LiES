#ifndef AC_BB_SOLVER_H
#define AC_BB_SOLVER_H

#include <climits>
#include "csp.h"
#include "ac_backtrack_solver.h"

/**
 * Branch and bound solver with arch consistency propagation
 * for minimization CSPs
 * with linear equations as constraints
 * Being X = {x1 ... xn} the set of variable of a CSP
 * bb_solver_t computes a solution {v1 ... vn} such that
 * min(sum_{i in [1..n]| i is even} xi)
 **/
class ac_bb_solver_t: public ac_backtrack_solver_t {

  protected:
    long min_value;
    int* min_solutions;

  public:
    ac_bb_solver_t(csp_t mcsp);

    virtual long evaluate_node(int* solution, int last);

    virtual bool solve(int* solutions);

    virtual bool solve_rec(int first, int* solutions);

};

#endif /* AC_BB_SOLVER_H */
