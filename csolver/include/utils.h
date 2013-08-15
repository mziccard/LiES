#ifndef UTILS_H
#define UTILS_H

#define DEBUG_LEVEL 0
#define INFO_LEVEL 	1
#define ERROR_LEVEL 2

#define INLINE 0
#define NEW_LINE 1

#define LOG_INFO


bool constraint_satisfied(int* coefs, int cterm, int* vars, int nvar);

void log(int level, int finalizer, const char* message, ...);

#endif /*UTILS_H*/
