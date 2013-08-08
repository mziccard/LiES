#ifndef SOLVER_H
#define SOLVER_H

#include "csp.h"

class solver_t {

public:

	virtual bool solve(int* solutions) = 0;

};

#endif /* SOLVER_H */
