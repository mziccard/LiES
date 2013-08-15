#include <cstdarg>
#include <stdio.h>
#include "utils.h"

bool constraint_satisfied(int* coefs, int cterm, int* vars, int nvar) {
  unsigned int i;
  int value = 0;
  for (i = 0; i < nvar; i++) {
    value += coefs[i]*vars[i];
  }
  if (value == cterm) {
    return true;
  }
  return false;
}

void log(int level, int finalizer, const char* format, ...) {
#if defined(LOG_ERROR) || defined(LOG_DEBUG) || defined(LOG_INFO)
  va_list list;
  va_start(list, format);
  if (level == ERROR_LEVEL) {
    if (finalizer == NEW_LINE) {
      printf("[ERROR]\t");
    }    
    vprintf(format, list);
  }
#endif
#if defined(LOG_DEBUG) || defined(LOG_INFO)
  if (level == INFO_LEVEL) {
    if (finalizer == NEW_LINE) {
      printf("[INFO]\t");
    } 
    vprintf(format, list);
  }
#endif
#if defined(LOG_DEBUG)
  if (level == DEBUG_LEVEL) {
    if (finalizer == NEW_LINE) {
      printf("[DEBUG]\t");
    } 
    vprintf(format, list);
  }
#endif
#if defined(LOG_ERROR) || defined(LOG_DEBUG) || defined(LOG_INFO)
  va_end(list);
#endif
}
