#include "ac_bb_solver.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

  ac_bb_solver_t::ac_bb_solver_t(csp_t mcsp): ac_backtrack_solver_t(mcsp), min_value(LONG_MAX) {
    min_solutions = (int*)malloc(csp.vnum * sizeof(int));
    memset(min_solutions, 0x0, csp.vnum * sizeof(int));
  }

  long ac_bb_solver_t::evaluate_node(int* solutions, int last) {
    long value = 0;
    unsigned int i;
    for (i = 0; i <= last; i++) {
      if (i%2 == 0 && assigned_variables[i]) {
        value += solutions[i];
      }
    }
    return value;
  }

  bool ac_bb_solver_t::solve(int* solutions) {
	  preprocess();
    stats.start_timer();
    solve_rec(0, solutions);
    stats.stop_timer();
    stats.print();
    memcpy(solutions, min_solutions, csp.vnum*sizeof(int));
    if (min_value != LONG_MAX) {
      return true;
    }
    return false;
  }

  bool ac_bb_solver_t::solve_rec(int first, int* solutions){
    log(DEBUG_LEVEL, NEW_LINE, "Backtrack for variable %d\n", first);

    if (evaluate_node(solutions, first) > min_value) {
      log(DEBUG_LEVEL, NEW_LINE, "Pruning subtree because of bound\n");
      return true;
    }
  
    domain_t& domain = csp.domains[first];
    domain_t backup_domain = domain.deep_copy();

	  propagate();
	  if (empty_domains()) {
    	return false;
  	}
  
    log(DEBUG_LEVEL, NEW_LINE, "Inspecting variable %d, with domain: ", first);
    domain.print();

    while (!domain.is_empty()) {
      log(DEBUG_LEVEL, NEW_LINE, "Entered while for variable %d\n", first);
      // Select and perform assignment
      assignment_t assignment = domain.select_assignment();
      domain.perform_assignment(assignment);

      log(DEBUG_LEVEL, NEW_LINE, "Found and performed assignment for variable %d = %d\n", first, assignment.value);

      solutions[first] = assignment.value;
      assigned_variables[first] = 1;

      stats.tick();

      // Check consistency
      if (is_consistent(solutions)) {
        if (first+1 == csp.vnum) {
          long evaluation = evaluate_node(solutions, first);
          if (evaluation < min_value) {
            min_value = evaluation;
            // DEBUG PURPOSE
            log(DEBUG_LEVEL, NEW_LINE, "Better solution found ");
            unsigned int i;
            for (i = 0; i < csp.vnum; i++) {
              log(DEBUG_LEVEL, INLINE, "x%d: %d ", i, solutions[i]);
            }
            log(DEBUG_LEVEL, INLINE, "value: %d\n", min_value);
            memcpy(min_solutions, solutions, csp.vnum*sizeof(int));
          }
          return true;
        } else { 
          solve_rec(first+1, solutions);
        }
      }
	    domain.revert_assignment(assignment);
    }

    domain.restore(backup_domain);
    assigned_variables[first] = 0;
    
    return true;
  }
