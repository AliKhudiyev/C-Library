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
    vec->_capacity = n_block ? n_block : 1;
    vec->_block_size = block_size ? block_size : 1;

    __allocate(&vec->_data, 0, vec->_block_size * vec->_capacity);

    return vec;
}

void CV_push_back(cvector* vec, const void* data){
    if(vec->_size >= vec->_capacity){
        vec->_capacity *= 2;
        __allocate(&vec->_data,
                 vec->_capacity*vec->_block_size/2,
                 vec->_capacity*vec->_block_size);
    }
    memcpy((char*)vec->_data+vec->_block_size*(vec->_size++), data, vec->_block_size);
}

unsigned CV_size_of(const cvector* vec){
    return vec->_size;
}

unsigned CV_capacity_of(const cvector* vec){
    return vec->_capacity;
}

void CV_clear(cvector* vec){
    vec->_size = 0;
}

void CV_copy(cvector* dest, const cvector* src){
    if(dest->_capacity < src->_size){
        __allocate(&dest->_data, dest->_capacity, src->_capacity);
        dest->_capacity = src->_capacity;
    }   memcpy(dest->_data, src->_data, src->_size * src->_block_size);
    dest->_size = src->_size;
    dest->_block_size = src->_block_size;
}

void CV_deep_copy(cvector* dest, const cvector* src){
    ;
}

unsigned CV_find(const cvector* vec, const void* data){
    for(unsigned i=0; i<vec->_size; ++i){
        if(!memcmp(vec->_data+vec->_block_size*i, data, vec->_block_size)) return i;
    }
    return -1;
}

void CV_delete(cvector* vec){
    vec->_size = vec->_capacity = vec->_block_size = 0;
    free(vec->_data);
    free(vec);
    
    vec->_data = NULL;
    vec = NULL;
}