
#ifndef _TYPES_
#define _TYPES_

#include <stdarg.h>

#define False 0
#define True 1

typedef unsigned char bool_t;
typedef void (*f_vvp_t)(void*);
typedef void (*f_vvpvpul_t)(void*, const void*, size_t);

// typedef struct{
//     void* _ptr;
// }cptr;

// CPtr_delete(cptr* ptr);
// CPtr_copy(cptr* dest, const cptr* src);

#endif
