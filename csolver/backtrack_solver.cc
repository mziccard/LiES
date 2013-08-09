#include "backtrack_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

backtrack_solver_t::backtrack_solver_t(csp_t mcsp) : csp(mcsp) {
  assigned_variables = (int*)malloc(csp.vnum * sizeof(int));
  memset(assigned_variables, 0x0, csp.vnum * sizeof(int));
}

bool backtrack_solver_t::is_consistent(int* solutions) {
  unsigned int i;
  bool constraints_satisfied = true;
  for (i = 0; i < csp.cnum && constraints_satisfied; i++) {
    int*c    = csp.coefs + csp.vnum*i;
    int term = csp.cterms[i];
    unsigned int j;
    // Avoid checking constraints
    unsigned int avoid = 0;
    for (j = 0; j < csp.vnum && !avoid; j++) {
      log(DEBUG_LEVEL, NEW_LINE, "Check variable %d for constraint %d\n", j, i);
      if ((assigned_variables[j]==0) && (c[j]!=0)) {
       log(DEBUG_LEVEL, NEW_LINE, "Constraint %d to avoid\n", i);
        avoid = 1;
      }
    }
    if (!avoid) {
      log(DEBUG_LEVEL, NEW_LINE, "Check constraint %d\n", i);
      constraints_satisfied = constraint_satisfied(c, term, solutions, csp.vnum);
    }
  }
  return constraints_satisfied;      
}

bool backtrack_solver_t::solve(int* solutions) {
  stats.start_timer();
  bool solution = solve_rec(0, solutions);
  stats.stop_timer();
  stats.print();
  return solution;
}

bool backtrack_solver_t::solve_rec(int first, int* solutions) {
  log(DEBUG_LEVEL, NEW_LINE, "Backtrack for variable %d\n", first);
     
  domain_t& domain = csp.domains[first];
  domain_t backup_domain = domain.deep_copy();
  bool solution_found = false;

  while (!domain.is_empty() && !solution_found) {
	stats.tick();
    log(DEBUG_LEVEL, NEW_LINE, "Entered while for variable %d\n", first);
    // Select and perform assignment
    assignment_t assignment = domain.select_assignment();
    domain.perform_assignment(assignment);

    log(DEBUG_LEVEL, NEW_LINE, "Found and performed assignment for variable %d\n", first);

    solutions[first] = assignment.value;
    assigned_variables[first] = 1;

    // Check consistency
    if (is_consistent(solutions)) {
      if (first+1 == csp.vnum) {
        return true;
      } else {
        solution_found = 
          solve_rec(first+1, solutions);
        if(!solution_found) {
          assigned_variables[first] = 0;
        }
      }
    }
	
	domain.revert_assignment(assignment);
  }

  if (!solution_found) {
    domain.restore(backup_domain);
    assigned_variables[first] = 0;
  }
  return solution_found;
}
