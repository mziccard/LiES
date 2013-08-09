#include "mc_backtrack_solver.h"

void mc_backtrack_solver_t::preprocess() {
  vector<int> variables_constraints(csp.vnum);
  unsigned int i;
  for (i = 0; i < csp.cnum; i++) {
    int* c = csp.coefs + (csp.cnum*i);
    unsigned int j;
    for (j = 0; j < csp.vnum; j++) {
      if (c[j] != 0) {
        variables_constraints[j]++;
      }
    }
  }
  for(i = 0; i < csp.vnum; i++) {
    vector<int>::iterator it = max_element(variables_constraints.begin(), variables_constraints.end());
    mc_ordered_variables[i] = distance(variables_constraints.begin(), it);
    *it = -1;   
  }
  log(DEBUG_LEVEL, NEW_LINE, "Preprocess ");
  for (i = 0; i < csp.vnum; i++) {
    log(DEBUG_LEVEL, INLINE, "%d ", mc_ordered_variables[i]);
  }
  log(DEBUG_LEVEL, INLINE, "\n");
}

mc_backtrack_solver_t::mc_backtrack_solver_t(csp_t mcsp) : backtrack_solver_t(mcsp) {
  mc_ordered_variables = (int*)malloc(csp.vnum * sizeof(int));
  memset(mc_ordered_variables, 0x0, csp.vnum * sizeof(int));
}

bool mc_backtrack_solver_t::solve(int* solutions) {
  preprocess();
  stats.start_timer();
  bool solution = solve_rec(0, solutions);
  stats.stop_timer();
  stats.print();
  return solution;
}

bool mc_backtrack_solver_t::solve_rec(int index, int* solutions) {
  int first = mc_ordered_variables[index];
  log(DEBUG_LEVEL, NEW_LINE, "Backtrack for variable %d\n", first);
  
  domain_t domain = csp.domains[first];
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
      if (index+1 == csp.vnum) {
        return true;
      } else {
        solution_found = 
          solve_rec(index+1, solutions);
        if(!solution_found) assigned_variables[first] = 0;
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
