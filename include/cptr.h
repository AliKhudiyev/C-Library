
#ifndef _POINTER_
#define _POINTER_

#include "ctypes.h"

typedef struct{
    size_t _size;
    void* _ptr;
    cptr* _child;
}cptr;

cptr* CPtr(size_t size);
void CPtr_init(size_t size);
void CPtr_assign(cptr* ptr, void* _ptr);
void CPtr_copy(cptr* dest, const cptr* src);
void CPtr_move(cptr* dest, cptr* src);
void* CPtr_ptr(const cptr* ptr);
void CPtr_delete(cptr* ptr);

#endif
