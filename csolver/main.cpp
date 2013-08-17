#include "lies.h"

int main(int argc, char** argv) {
  
  char* input_file = 0;
  char* input_string = 0;

  int resolution_mode = 0;
  int i = 0;
  while(i < argc) {
    if (strcmp("-input-file", argv[i])==0) {
      i = i+1;
      if (i < argc) {
        input_file = argv[i];
      } else {
        log(ERROR_LEVEL, NEW_LINE, "Invalid input file argument\n");
        return false;
      }
    }
    else {
      if (strcmp("-resolution-mode", argv[i])==0) {
        i = i+1;
        if (i < argc) {
          resolution_mode = atoi(argv[i]);
        } else {
          log(ERROR_LEVEL, NEW_LINE, "Invalid resolution mode argument\n");
          return false;
        }
      } else {
        input_string = argv[i];
      }
    }
    i++;
    
  }

	//log(INFO_LEVEL, NEW_LINE, "BACKTRACK\n");
	//solve(filename, 0);
	
  if (input_file != 0) {    
    solve(input_file, resolution_mode, 1);
  } else {
    solve(input_string, resolution_mode, 0);
  }
	
	//log(INFO_LEVEL, NEW_LINE, "AC_BACKTRACK\n");
	//solve(filename, 2);
		
	return true;	
}
