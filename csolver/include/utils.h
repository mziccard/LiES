#ifndef UTILS_H
#define UTILS_H

#define DEBUG_LEVEL 0
#define ERROR_LEVEL 1

#define INLINE 0
#define NEW_LINE 1

#define LOG_DEBUG


bool constraint_satisfied(int* coefs, int cterm, int* vars, int nvar);

void log(int level, int finalizer, const char* message, ...);

#endif /*UTILS_H*/
