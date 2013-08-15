#include "csp_reader.h"

#define CHECK_ERR if (ERROR) { return false; }

	csp_reader_t::csp_reader_t(const char* filename) : ERROR(0) {

		FILE *fp = fopen(filename, "rb");
		if (!fp) {
			ERROR = 1;
			return;
		}
	
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		std::vector<char> buffer(size + 1);
		fread (&buffer[0], 1, size, fp);
		fclose(fp);

		char *errorPos = 0;
		char *errorDesc = 0;
		int errorLine = 0;
		block_allocator allocator(1 << 10);
	
		root = json_parse(&buffer[0], &errorPos, &errorDesc, &errorLine, &allocator);
    if (!root) {
      ERROR = 1;
    }
	}

  bool csp_reader_t::read_error() {
    return ERROR;
  }

	bool csp_reader_t::read_vnum(int& vnum) {
		CHECK_ERR
    if (root->type == JSON_OBJECT) {
		for (json_value *it = root->first_child; it; it = it->next_sibling) {
			if (it->name[0] == 'v' && it->name[1] == 'n' && it->type == JSON_INT) {
				vnum = it->int_value;
				return true;
			}
		}
		return false;
	}
	return false;
		
	}

	bool csp_reader_t::read_cnum(int& cnum) {
    CHECK_ERR
	  if (root->type == JSON_OBJECT) {
		  for (json_value *it = root->first_child; it; it = it->next_sibling) {
			  if (it->name[0] == 'c' && it->name[1] == 'n' && it->type == JSON_INT) {
				  cnum = it->int_value;
				  return true;
			  }
		  }
		  return false;
	  }
	  return false;
  }

	bool csp_reader_t::read_domains(domain_t* domains, int num) {
    CHECK_ERR
    if (root->type == JSON_OBJECT) {
		  for (json_value *it = root->first_child; it; it = it->next_sibling) {
			  if (it->name[0] == 'd' && it->name[1] == 'o' && it->type == JSON_ARRAY) {
				  unsigned int i = 0;
				  for (json_value *it2 = it->first_child; it2 && i < num; it2 = it2->next_sibling)
				  {
					  if (it2->type == JSON_ARRAY) {
						  json_value* l = it2->first_child;
						  json_value* h = l->next_sibling;
						  domain_t domain;
						  interval_t interval;
						  if (l->type == JSON_INT && h->type == JSON_INT) {
							  interval.l = l->int_value;
							  interval.h = h->int_value;
							  domain.intervals.push_back(interval);
							  domains[i] = domain;
						  } else {
							  return false;
						  }
					  } else {
						  return false;
					  }
					  i++;
				  }
				  return true;
			  }
		  }
		  return false;
	  }
	  return false;
  }

	bool csp_reader_t::read_coefs(int* coefs, int num) {
    CHECK_ERR
	  if (root->type == JSON_OBJECT) {
		  json_value *it = root->first_child;
		  while (it) {
			  if ( it->name[0] == 'c' && it->name[1] == 'o' && it->type == JSON_ARRAY) {
				  unsigned int i = 0;
				  for (json_value *it2 = it->first_child; it2 && i < num; it2 = it2->next_sibling)
				  {
					  if (it2->type == JSON_INT) {
					   	coefs[i] = it2->int_value;
					  } else {
						  return false;
					  }
					  i++;
				  }
				  return true;
			  }
			  it = it->next_sibling;
		  }
		  return false;
	  }
	  return false;
  }

	bool csp_reader_t::read_cterms(int* cterms, int num) {
	  if (root -> type == JSON_OBJECT) {
		  json_value *it = root->first_child;
		  while (it) {
			  if ( it->name[0] == 'c' && it->name[1] == 't' && it->type == JSON_ARRAY) {
				  unsigned int i = 0;
				  for (json_value *it2 = it->first_child; it2 && i < num; it2 = it2->next_sibling)
				  {	
					  if (it2->type == JSON_INT) {
						  cterms[i] = it2->int_value;
					  } else {
						  return false;
					  }
					  i++;
				  }
				  return true;
			  }
			  it = it->next_sibling;
		  }
		  return false;
	  }
	  return false;
  }


