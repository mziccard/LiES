#ifndef LIES_H
#define LIES_H

#include "backtrack_solver.h"
#include "mc_backtrack_solver.h"
#include "ac_backtrack_solver.h"
#include "bb_solver.h"
#include "ac_bb_solver.h"
#include "csp_reader.h"
#include "utils.h"
#include <stdio.h>

#define BACKTRACK         0
#define MC_BACKTRACK      1
#define AC_BACKTRACK      2
#define BRANCH_BOUND      3
#define AC_BRANCH_BOUND   4


void solve(const char* filename, int resolution_type) {
 
  csp_reader_t csp_reader(filename);

	FILE *fp = fopen(filename, "rb");
	if (csp_reader.read_error()) {
		log(ERROR_LEVEL, NEW_LINE, "Error opening file %s\n", filename);
		return;
	}
 	
	int variables_num;
	int constraints_num;		

	csp_reader.read_vnum(variables_num);
	csp_reader.read_cnum(constraints_num);

	log(DEBUG_LEVEL, NEW_LINE, "Variable nums %d constraints num %d\n", variables_num, constraints_num);
	
	domain_t domains[variables_num];
	int coefs[constraints_num][variables_num];
	int cterms[constraints_num];

	csp_reader.read_coefs(&coefs[0][0], variables_num*constraints_num);
	csp_reader.read_cterms(cterms, constraints_num);
	csp_reader.read_domains(domains, variables_num);

	unsigned int i;
	unsigned int j;
	for(i=0; i<constraints_num; i++) {
    log(DEBUG_LEVEL, NEW_LINE, "");
		for(j=0; j<variables_num; j++) {
			log(DEBUG_LEVEL, INLINE, "%d ", coefs[i][j]);
		}
		log(DEBUG_LEVEL, INLINE, "\n");
	}

  log(DEBUG_LEVEL, NEW_LINE, "");
	for(i=0; i<constraints_num; i++) {
		log(DEBUG_LEVEL, INLINE, "%d ", cterms[i]);
	}
	log(DEBUG_LEVEL, INLINE, "\n");
	
  log(DEBUG_LEVEL, NEW_LINE, "[");
	for(i=0; i<variables_num; i++) {
		log(DEBUG_LEVEL, INLINE, "[%d, %d] ", domains[i].intervals[0].l, domains[i].intervals[0].h);
	}
	log(DEBUG_LEVEL, INLINE, "]\n");

	csp_t csp(&coefs[0][0], cterms, domains, variables_num, constraints_num);

  solver_t* solver;
  switch (resolution_type) {
    case BACKTRACK:         solver = new backtrack_solver_t(csp);
                            break;
    case MC_BACKTRACK:      solver = new mc_backtrack_solver_t(csp);
                            break;
    case AC_BACKTRACK:      solver = new ac_backtrack_solver_t(csp);
                            break;
    case BRANCH_BOUND:      solver = new bb_solver_t(csp);
                            break;
    case AC_BRANCH_BOUND:   solver = new ac_bb_solver_t(csp);
                            break;
  }

	int solutions[variables_num];

	if (solver->solve(solutions)) {
    log(INFO_LEVEL, NEW_LINE, "[Sol]\t ");
    for(i=0; i<variables_num; i++) {
      log(INFO_LEVEL, INLINE, "x%d = %d ", i, solutions[i]);
    }
    log(INFO_LEVEL, INLINE, "\n");
  }
		
  delete solver;
	return;		
}

#endif /* LIES_H */
