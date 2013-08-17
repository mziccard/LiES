#ifndef CSP_READER_H
#define CSP_READER_H

#include <stdio.h>
#include <string.h>
#include "json.h"
#include "csp.h"

class csp_reader_t {

private:
	int 			ERROR;
	json_value* 	root;

public:
	
	csp_reader_t(const char* filename, int id);

	csp_reader_t(char* input_string);

	bool read_error();

	bool read_vnum(int& vnum);

	bool read_cnum(int& cnum);

	bool read_domains(domain_t* domains, int num);

	bool read_coefs(int* coefs, int num);

	bool read_cterms(int* cterms, int num);

};

#endif /* CSP_READER_H */
