#include "cvector.h"

#include <stdio.h>

// Allocator
void __allocate(void** ptr, size_t size, size_t new_size){
    void* cptr = *ptr;
    
    *ptr = malloc(new_size);
    if(*ptr == NULL){
        fprintf(stderr, "%s", "__allocate: failed to allocate!\n");
        exit(1);
    }
    memcpy(*ptr, cptr, size);
    if(size){ free(cptr); }
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Constructor and Destructor
cvector* CVector(size_t block_size, size_t n_block){
    cvector* vec = NULL;

    __allocate((void**)&vec, 0, sizeof(cvector));
    CV_init(vec, block_size, n_block);

    return vec;
}

void CV_init(cvector* vec, size_t block_size, size_t n_block){
    if(!vec) return ;

    vec->_size = 0;
    vec->_capacity = n_block ? n_block : 1;
    vec->_block_size = block_size ? block_size : 1;
    vec->_data = NULL;
    vec->_copy = NULL;
    vec->_delete = NULL;
    __allocate(&vec->_data, 0, vec->_block_size * vec->_capacity);
}

void CV_delete(cvector* vec){
    if(!vec){ printf("-\n"); return ;}

    // printf("+\n");
    // CV_delete_elements(vec);
    free(vec->_data);
    vec->_size = vec->_capacity = vec->_block_size = 0;
    vec->_data = NULL;
}

void CV_delete_elements(cvector* vec){
    if(!vec->_delete) return ;

    for(size_t i=0; i<vec->_size; ++i){
        vec->_delete(CV_at(vec, i));
    }
}

void CV_delete_recursive(void* vec){
    if(!vec) return ;

    cvector* vec_ = (cvector*)vec;
    CV_delete_elements(vec_);
    free(vec_->_data);
    vec_->_size = vec_->_capacity = vec_->_block_size = 0;
    vec_->_data = NULL;
}

void CV_destruct(void* vec){
    CV_delete_recursive(vec);
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
    if(vec->_capacity < n){
        vec->_capacity = n;
        __allocate(&vec->_data, vec->_capacity, n);
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
        vec->_capacity = vec->_size;
        __allocate(&vec->_data, vec->_size*vec->_block_size, vec->_size*vec->_block_size);
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
    if(!vec->_size) return NULL;
    return vec->_data;
}

void* CV_back(const cvector* vec){
    if(!vec->_size) return NULL;
    return vec->_data+(vec->_size-1)*vec->_block_size;
}

void* CV_data(const cvector* vec){
    return vec->_data;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CV_assign(cvector* vec1, const cvector* vec2, size_t pos, size_t size){
    if(vec1->_block_size != vec2->_block_size) return ;
    if(size == -1) size = vec2->_size;
    if(pos >= vec2->_size || pos + size > vec2->_size) return ;

    CV_delete_elements(vec1);
    if(vec1->_capacity < size){
        __allocate(&vec1->_data, 
                    vec1->_capacity * vec1->_block_size,
                    vec2->_capacity * vec2->_block_size);
        vec1->_capacity = vec2->_capacity;
    }
    memcpy(vec1->_data, 
           vec2->_data + pos * vec2->_block_size, 
           size * vec2->_block_size);
    vec1->_size = size;
}

void CV_push_back(cvector* vec, const void* data){
    if(vec->_size == vec->_capacity){
        vec->_capacity *= 2;
        __allocate(&vec->_data,
                 vec->_capacity*vec->_block_size/2,
                 vec->_capacity*vec->_block_size);
    }
    memcpy(vec->_data+(vec->_size++)*vec->_block_size, data, vec->_block_size);
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
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CV_enlarge(cvector* vec, size_t n){
    if(vec->_size+n-1 >= vec->_capacity){
        vec->_capacity = vec->_size+n;
        __allocate(&vec->_data,
                   vec->_size*vec->_block_size,
                   vec->_capacity*vec->_block_size);
    }
}

void CV_set_destructor(cvector* vec, void (*destructor)(void*)){
    vec->_delete = destructor;
}

void CV_set_deep_copy(cvector* vec, void (*copy)(void* dest, const void* src, size_t n_byte)){
    vec->_copy = copy;
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
    if(dest->_block_size != src->_block_size) return ;

    CV_delete_elements(dest);
    if(dest->_capacity < src->_size){
        __allocate(&dest->_data, dest->_capacity*dest->_block_size, src->_capacity*src->_block_size);
        dest->_capacity = src->_capacity;
    }   memcpy(dest->_data, src->_data, src->_size * src->_block_size);
    dest->_size = src->_size;
    dest->_block_size = src->_block_size;
}

void CV_deep_copy(cvector* dest, const cvector* src){
    if(!dest->_copy || dest->_block_size != src->_block_size) return ;

    CV_delete_elements(dest);
    if(dest->_capacity < src->_size){
        __allocate(&dest->_data, dest->_capacity*dest->_block_size, src->_capacity*src->_block_size);
        dest->_capacity = src->_capacity;
    }
    dest->_copy(dest->_data, src->_data, src->_size * src->_block_size);
    dest->_size = src->_size;
    dest->_block_size = src->_block_size;
}

size_t CV_find(const cvector* vec, const void* val){
    for(unsigned i=0; i<vec->_size; ++i){
        if(!memcmp(vec->_data+vec->_block_size*i, val, vec->_block_size)) return i;
    }
    return -1;
}
// = = = = = = = = = = = = = = = = = = = = = = =