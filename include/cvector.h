
#ifndef _VECTOR_
#define _VECTOR_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

#include "ctypes.h"

typedef enum{
    Char = 0,
    Int,
    Float,
    Double,
    String
}__Type;

typedef struct{
    unsigned _size, _capacity, _block_size;
    void* _data;
}cvector;

#define MCV_push_back(vec, data, _type)                                     \
    if(vec->_size >= vec->_capacity){                                   \
        vec->_capacity *= 2;                                            \
        __allocate(&vec->_data,                                         \
                 vec->_capacity*vec->_block_size/2,                     \
                 vec->_capacity*vec->_block_size);                      \
    }   memcpy((_type*)vec->_data+vec->_size++, data, sizeof(_type));

#define MCV_force_push_back(vec, data, _type)                               \
    {                                                                   \
        _type tmp = data;                                               \
        MCV_push_back(vec, &tmp, _type);                                    \
    }

#define MCV_get_ptr(vec, index, _type)                                      \
    ((_type*)(index < vec->_size? (_type*)vec->_data+index : NULL))

#define MCV_enlarge(vec, n, _type)                                          \
    if(vec->_size+n-1 >= vec->_capacity){                               \
        vec->_capacity += n;                                            \
        __allocate(&vec->_data,                                         \
                 (vec->_capacity-n)*vec->_block_size,                   \
                 vec->_capacity*vec->_block_size);                      \
    }

#define MCV_insert(vec, index, data, _type)                                 \
    if(index >= 0 && index <= vec->_size)                               \
    {                                                                   \
        MCV_enlarge(vec, 1, _type)                                          \
        for(unsigned i=0; i<vec->_size-index; ++i){                     \
            memcpy((_type*)vec->_data+vec->_size-i,                     \
                (_type*)vec->_data+vec->_size-1-i,                      \
                sizeof(_type));                                         \
        }   memcpy((_type*)vec->_data+index, data, sizeof(_type));      \
        ++vec->_size;                                                   \
    }

#define MCV_pop_back(vec, _type)                                            \
    MCV_get_ptr(vec, --vec->_size, _type)

#define MCV_erase(vec, index, _type)                                                \
    for(unsigned i=index; index >= 0 && i<vec->_size-1; ++i){                   \
        memcpy((_type*)vec->_data+i, (_type*)vec->_data+i+1, sizeof(_type));    \
    }   --vec->_size;

#define MCV_force_find(vec, data, _type, _result)                                   \
    {                                                                           \
        _type tmp = data;                                                       \
        _result = CV_find(vec, &tmp)                                \
    }

#define MCV_check(vec, data, _result)                                       \
    _result = CV_find(vec, data); \
    if(_result == -1){ _result = 0; }                                           \
    else{ _result = 1; }

#define MCV_force_check(vec, data, _type, _result)\
    MCV_force_find(vec, data, _type, _result) \
    if(_result == -1){ _result = 0; }                                           \
    else{ _result = 1; }

#define MCV_swap(vec, index1, index2, _type)                                                \
    if(index1 < vec->_size && index2 < vec->_size)                                      \
    {                                                                                   \
        _type* tmp = malloc(sizeof(_type));                                             \
        memcpy(tmp, (_type*)vec->_data+index1, sizeof(_type));                          \
        memcpy((_type*)vec->_data+index1, (_type*)vec->_data+index2, sizeof(_type));    \
        memcpy(((_type*)vec->_data)+index2, tmp, sizeof(_type));                        \
        free((void*)tmp);                                                               \
    }

#define MCV_sort(vec, _sorter, _type)                                                   \
    for(unsigned i=0; i<vec->_size; ++i){                                           \
        for(unsigned j=0; j<vec->_size-1; ++j){                                     \
            if(_sorter(((_type*)vec->_data)[j], ((_type*)vec->_data)[j+1])){        \
                MCV_swap(vec, j, j+1, _type);                                           \
            }                                                                       \
        }                                                                           \
    }

#define MCV_apply_sort(vec, sorter) \
    sorter(vec->_data, vec->_size)

#define MCV_apply(function) \
    function(vec->_data, vec->_size, vec->_capacity, vec->_block_size)

//
void __allocate(void** ptr, unsigned size, unsigned new_size);
// =======================

cvector* CVector(unsigned block_size, unsigned n_block);
void CV_push_back(cvector* vec, const void* data);
unsigned CV_size_of(const cvector* vec);
unsigned CV_capacity_of(const cvector* vec);
void CV_clear(cvector* vec);
void CV_copy(cvector* dest, const cvector* src);
void CV_deep_copy(cvector* dest, const cvector* src);
unsigned CV_find(const cvector* vec, const void* data);
void CV_delete(cvector* vec);

#endif
