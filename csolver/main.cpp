#include "backtrack_solver.h"
#include "mc_backtrack_solver.h"
#include "ac_backtrack_solver.h"
#include "bb_solver.h"
#include "ac_bb_solver.h"
#include "csp_reader.h"
#include "utils.h"
#include <stdio.h>

int main(int argc, char** argv) {

	const char* filename = "csp.json";
	csp_reader_t csp_reader(filename);
	

	FILE *fp = fopen(filename, "rb");
	if (csp_reader.read_error()) {
		log(ERROR_LEVEL, NEW_LINE, "Error opening file %f\n", filename);
		return 0;
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
	ac_backtrack_solver_t solver(csp);

	int solutions[variables_num];

	if (solver.solve(solutions))
		log(DEBUG_LEVEL, NEW_LINE, "Solution X0 = %d, X1 = %d, X2 = %d\n", solutions[0], solutions[1], solutions[2]);
		
	return true;	
}
