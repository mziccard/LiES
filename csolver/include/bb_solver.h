#ifndef BB_SOLVER_H
#define BB_SOLVER_H

#include <climits>
#include "csp.h"
#include "backtrack_solver.h"

/**
 * Branch and bound solver for minimization CSPs
 * with linear equations as constraints
 * Being X = {x1 ... xn} the set of variable of a CSP
 * bb_solver_t computes a solution {v1 ... vn} such that
 * min(sum_{i in [1..n]| i is even} xi)
 **/
class bb_solver_t: public backtrack_solver_t {

  protected:
    long min_value;
    int* min_solutions;

  public:
    bb_solver_t(csp_t mcsp);

    virtual long evaluate_node(int* solution, int last);

    virtual bool solve(int* solutions);

    virtual bool solve_rec(int first, int* solutions);

};

#endif /* BB_SOLVER_H */

