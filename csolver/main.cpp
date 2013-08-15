#include "lies.h"

int main(int argc, char** argv) {

	const char* filename = "test/cspg.json";
	//log(INFO_LEVEL, NEW_LINE, "BACKTRACK\n");
	//solve(filename, 0);
	log(INFO_LEVEL, NEW_LINE, "MC_BACKTRACK\n");
	solve(filename, 1);
	//log(INFO_LEVEL, NEW_LINE, "AC_BACKTRACK\n");
	//solve(filename, 2);
		
	return true;	
}
