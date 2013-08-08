#include "ac_backtrack_solver.h"

void ac_backtrack_solver_t::preprocess() {
  unsigned int i;
  for (i = 0; i < csp.cnum; i++) {
    int* c = csp.coefs + (i*csp.cnum);
    unsigned int j, var1, var2, vcount = 0;
    for (j = 0; (j < csp.vnum) && (vcount < 3); j++) {
      if (c[j] != 0) {
         log(DEBUG_LEVEL, NEW_LINE, "Not 0 variable %d for constraint %d\n", j, i);
        if (vcount == 0) {
          var1 = j;
        } else if (vcount == 1) {
          var2 = j;
        }
        vcount++;
      }
    }
    
    if (vcount == 2) { 
      log(DEBUG_LEVEL, NEW_LINE, "Binary constraint identified %d: var%d <-> var%d\n", i, var1, var2);
      binary_constraint_t constraint1;
      constraint1.id = i;
      constraint1.var1 = var1;
      constraint1.var2 = var2;
      binary_constraints.push_back(constraint1);  
      // Removing the following makes arch consistency
      // directional
      binary_constraint_t constraint2;
      constraint2.id = i;
      constraint2.var1 = var2;
      constraint2.var2 = var1;
      binary_constraints.push_back(constraint2);       
    }
  }
}

void ac_backtrack_solver_t::propagate() {
  vector<binary_constraint_t> constraints = binary_constraints;
  
  while (!constraints.empty()) {
    vector<binary_constraint_t>::iterator constraint = constraints.begin();
    log(DEBUG_LEVEL, NEW_LINE, "Propagation for constraint %d: var%d -> var%d\n", constraint->id, constraint->var1, constraint->var2);
    int cterm = csp.cterms[constraint->id];
    int* c = csp.coefs + (csp.cnum * (constraint->id));
    domain_t& domain1 = csp.domains[constraint->var1];
    domain_t& domain2 = csp.domains[constraint->var2];
    bool domain_changed = false;
    unsigned int interval1_id;
    for (interval1_id = 0; interval1_id < domain1.intervals.size(); interval1_id++) {
      interval_t& interval1 = domain1.intervals[interval1_id];
      int value1;
      for (value1 = interval1.l; value1 <= interval1.h; value1++) {
        bool consistent = false;
        vector<interval_t>::iterator interval2;
        unsigned int interval2_id;
        for (interval2_id = 0; interval2_id < domain2.intervals.size() && !consistent; interval2_id++) {
          interval_t& interval2 = domain2.intervals[interval2_id];
          int value2;
          for (value2 = interval2.l; value2 <= interval2.h; value2++) {
            if ((c[constraint->var1]*value1) == (cterm - c[constraint->var2]*value2)) {
              consistent = true;
            }
          }
        }
        if (!consistent) {
          domain_changed = true;
          log(DEBUG_LEVEL, NEW_LINE, "Deleting from domain %d value %d\n", constraint->var1, value1);
          // Remove value1 from the domain
          domain1.split(interval1_id, value1);
        }            
      }   
    }
    if (domain_changed) {
      vector<binary_constraint_t>::iterator new_constraint;
      for (new_constraint = binary_constraints.begin(); new_constraint != binary_constraints.end(); new_constraint++) {
        if (constraint->var1 == new_constraint->var2) {
          bool found = false;
          unsigned int i;
          for (i = 0; i < constraints.size() && !found; i++) {
            if (constraints[i].id == new_constraint->id && 
              constraints[i].var1 == new_constraint->var1 && 
              constraints[i].var2 == new_constraint->var2) {
              found = true;
            }
          }
          if (!found) { 
            constraints.push_back(*new_constraint); 
            log(DEBUG_LEVEL, NEW_LINE, "Added constraint to be checked x%d -> x%d\n", new_constraint->var1, new_constraint->var2);
          }
        }
      }
    }
    constraints.erase(constraint);        
  }
}

bool ac_backtrack_solver_t::solve(int* solutions) {
  preprocess();
  stats.start_timer();
  bool solution = solve_rec(0, solutions);
  stats.stop_timer();
  stats.print();
  return solution;
}

bool ac_backtrack_solver_t::solve_rec(int first, int* solutions) {
    
  domain_t& domain = csp.domains[first];
  domain_t backup_domain = domain.deep_copy();
  bool solution_found = false;

  propagate();

  log(DEBUG_LEVEL, NEW_LINE, "Inspecting variable %d, with domain: ", first);
  domain.print();

  while (!domain.is_empty() && !solution_found) {
    stats.tick();
    // Select and perform assignment
    assignment_t assignment = domain.select_assignment();
    domain.perform_assignment(assignment);

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
