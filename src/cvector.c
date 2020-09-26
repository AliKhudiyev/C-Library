#include "cvector.h"

#include <stdio.h>

// Allocator
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
// = = = = = = = = = = = = = = = = = = = = = = =

// Constructor and Destructor
cvector* CVector(unsigned block_size, unsigned n_block){
    cvector* vec = malloc(sizeof(cvector));

    vec->_size = 0;
    vec->_capacity = n_block ? n_block : 1;
    vec->_block_size = block_size ? block_size : 1;

    __allocate(&vec->_data, 0, vec->_block_size * vec->_capacity);

    return vec;
}

void CV_delete(cvector* vec){
    vec->_size = vec->_capacity = vec->_block_size = 0;
    free(vec->_data);
    free(vec);
    
    vec->_data = NULL;
    vec = NULL;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void* CV_begin(const cvector* vec){
    return vec->_data;
}

void* CV_end(const cvector* vec){
    return vec->_data+vec->_block_size*(vec->_size-1);
}

const void* CV_cbegin(const cvector* vec){
    return (const void*)vec->_data;
}

const void* CV_cend(const cvector* vec){
    return (const void*)vec->_data+vec->_block_size*(vec->_size-1);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
size_t CV_size(const cvector* vec){
    return vec->_size;
}

void CV_resize(cvector* vec, size_t n){
    if(n > vec->_capacity){
        __allocate(&vec->_data, vec->_capacity, n);
        vec->_capacity = n;
    }
}

size_t CV_capacity(const cvector* vec){
    return vec->_capacity;
}

bool_t CV_empty(const cvector* vec){
    return vec->_size == 0;
}

void CV_shrink_to_fit(cvector* vec){
    if(vec->_capacity > vec->_size){
        ;
    }
}

size_t CV_block_size(const cvector* vec){
    return vec->_block_size;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CV_at(const cvector* vec, size_t position){
    if(position < vec->_size){
        return vec->_data+position*vec->_block_size;
    }
    return NULL;
}

void* CV_front(const cvector* vec){
    return vec->_data;
}

void* CV_back(const cvector* vec){
    return vec->_data+(vec->_size-1)*vec->_block_size;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CV_push_back(cvector* vec, const void* data){
    if(vec->_size >= vec->_capacity){
        vec->_capacity *= 2;
        __allocate(&vec->_data,
                 vec->_capacity*vec->_block_size/2,
                 vec->_capacity*vec->_block_size);
    }
    memcpy((char*)vec->_data+vec->_block_size*(vec->_size++), data, vec->_block_size);
}

void CV_pop_back(cvector* vec){
    if(vec->_size > 0) --vec->_size;
}

void CV_insert(cvector* vec, size_t position, const void* val){
    if(position <= vec->_size){
        CV_enlarge(vec, 1);
        for(size_t i=0; i<vec->_size-position; ++i){
            memcpy(vec->_data+(vec->_size-i)*vec->_block_size,
                   vec->_data+(vec->_size-1-i)*vec->_block_size,
                   vec->_block_size);
        }   memcpy(vec->_data+position*vec->_block_size, val, vec->_block_size);
        ++vec->_size;
    }
}

void CV_erase(cvector* vec, size_t position){
    if(!vec->_size) return;
    for(size_t i=position; i<vec->_size-1; ++i){
        memcpy(vec->_data+i*vec->_block_size, vec->_data+(i+1)*vec->_block_size, vec->_block_size);
    }   --vec->_size;
}

void CV_swap(cvector* vec1, cvector* vec2){
    size_t tmp;

    tmp = vec1->_size;
    vec1->_size = vec2->_size;
    vec2->_size = tmp;

    tmp = vec1->_capacity;
    vec1->_capacity = vec2->_capacity;
    vec2->_capacity = tmp;

    tmp = vec1->_block_size;
    vec1->_block_size = vec2->_block_size;
    vec2->_block_size = tmp;

    void* _tmp;
    _tmp = vec1->_data;
    vec1->_data = vec2->_data;
    vec2->_data = _tmp;
}

void CV_clear(cvector* vec){
    vec->_size = 0;
}

void CV_emplace(cvector* vec, size_t position, ...){
    ;
}

void CV_emplace_back(cvector* vec, ...){
    // CV_emplace(vec, vec->_size, ...);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CV_enlarge(cvector* vec, size_t n){
    if(vec->_size+n-1 >= vec->_capacity){
        vec->_capacity += n;
        __allocate(&vec->_data,
                 (vec->_capacity-n)*vec->_block_size,
                 vec->_capacity*vec->_block_size);
    }
}

void CV_swap_val(cvector* vec, size_t pos1, size_t pos2){
    if(pos1<vec->_size && pos2<vec->_size){
        void* tmp;
        __allocate(&tmp, 0, vec->_block_size);
        memcpy(tmp, vec->_data+pos1*vec->_block_size, vec->_block_size);
        memcpy(vec->_data+pos1*vec->_block_size, vec->_data+pos2*vec->_block_size, vec->_block_size);
        memcpy(vec->_data+pos2*vec->_block_size, tmp, vec->_block_size);
        free(tmp);
    }
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
// = = = = = = = = = = = = = = = = = = = = = = =