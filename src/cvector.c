#include "cvector.h"

#include <stdio.h>

void __allocate(void** ptr, unsigned size, unsigned new_size){
    if(size != new_size){
        void* cptr = *ptr;

        *ptr = malloc(new_size);
        if(*ptr == NULL){
            fprintf(stderr, "%s", "__allocate: failed to allocate!\n");
            exit(1);
        }
        memcpy(*ptr, cptr, size);
        if(size) free(cptr);
    }
}

// =========================

cvector* CVector(unsigned block_size, unsigned n_block){
    cvector* vec = malloc(sizeof(cvector));

    vec->_size = 0;
    vec->_capacity = n_block;
    vec->_block_size = block_size;

    unsigned sz = block_size * n_block? block_size * n_block : 1;
    __allocate(&vec->_data, 0, sz);

    return vec;
}

unsigned size_of_cvector(const cvector* vec){
    return vec->_size;
}

unsigned capacity_of_cvector(const cvector* vec){
    return vec->_capacity;
}

void clear_cvector(cvector* vec){
    vec->_size = 0;
}

void copy_cvector(cvector* dest, const cvector* src){
    if(dest->_capacity < src->_size){
        __allocate(&dest->_data, dest->_capacity, src->_capacity);
        dest->_capacity = src->_capacity;
    }   memcpy(dest->_data, src->_data, src->_size * src->_block_size);
    dest->_size = src->_size;
    dest->_block_size = src->_block_size;

    printf("%u ; %u\n", src->_size, src->_block_size);
}

void deep_copy_vector(cvector* dest, const cvector* src){
    ;
}

void delete_cvector(cvector* vec){
    vec->_size = vec->_capacity = 0;
    free(vec->_data);
    vec->_data = NULL;
}