#include "cvector.h"

void allocate(void** ptr, unsigned size, unsigned new_size){
    if(size != new_size){
        void* cptr = *ptr;

        *ptr = malloc(new_size);
        memcpy(*ptr, cptr, size);
        if(!size) free(cptr);
    }
}

// =========================

cvector* CVector(unsigned size, unsigned n_block){
    cvector* vec = malloc(sizeof(cvector));

    vec->_size = 0;
    vec->_capacity = n_block;
    vec->_block_size = size;

    unsigned sz = size * n_block? size * n_block : 1;
    allocate(&vec->_data, 0, sz);

    return vec;
}

unsigned size_of(const cvector* vec){
    return vec->_size;
}

unsigned capacity_of(const cvector* vec){
    return vec->_capacity;
}

void clear(cvector* vec){
    vec->_size = 0;
}

void copy_cvector(cvector* dest, const cvector* src){
    ;
}

void delete_cvector(cvector* vec){
    vec->_size = vec->_capacity = 0;
    free(vec->_data);
    vec->_data = NULL;
}