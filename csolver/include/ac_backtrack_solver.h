#ifndef AC_BACKTRACK_SOLVER_H
#define AC_BACKTRACK_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csp.h"
#include "utils.h"
#include "backtrack_solver.h"

using namespace std;

class ac_backtrack_solver_t: public backtrack_solver_t {
  private:
    // Contains ids of all binary constraints
    vector<binary_constraint_t> binary_constraints;

  protected:

    void preprocess();

  public:
    ac_backtrack_solver_t(csp_t mcsp) : backtrack_solver_t(mcsp) {
    }

    virtual void propagate();

	virtual bool empty_domains();

    virtual bool solve(int* solutions);

    virtual bool solve_rec(int first, int* solutions);
};

#endif /* AC_BACKTRACK_SOLVER_H */
