
#ifndef _TYPES_
#define _TYPES_

#include <stdarg.h>

#include "calgorithm.h"

#define False 0
#define True 1

typedef unsigned char bool_t;
typedef void (*f_copy_t)(void*, const void*, size_t);
typedef void (*f_destructor_t)(void*);
typedef const char* (*f_printer_t)(void*);

#endif
