
#ifndef _VECTOR_
#define _VECTOR_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

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

#define push_back(vec, data, _type)                                     \
    if(vec->_size >= vec->_capacity){                                   \
        vec->_capacity *= 2;                                            \
        __allocate(&vec->_data,                                         \
                 vec->_capacity*vec->_block_size/2,                     \
                 vec->_capacity*vec->_block_size);                      \
    }   memcpy((_type*)vec->_data+vec->_size++, data, sizeof(_type));

#define force_push_back(vec, data, _type)                               \
    {                                                                   \
        _type tmp = data;                                               \
        push_back(vec, &tmp, _type);                                    \
    }

#define get_ptr(vec, index, _type)                                      \
    ((_type*)(index < vec->_size? (_type*)vec->_data+index : NULL))

#define enlarge(vec, n, _type)                                          \
    if(vec->_size+n-1 >= vec->_capacity){                               \
        vec->_capacity += n;                                            \
        __allocate(&vec->_data,                                         \
                 (vec->_capacity-n)*vec->_block_size,                   \
                 vec->_capacity*vec->_block_size);                      \
    }

#define insert(vec, index, data, _type)                                 \
    enlarge(vec, 1, _type)                                              \
    ++vec->_size;                                                       \
    for(unsigned i=0; i<vec->_size-index; ++i){                         \
        memcpy((_type*)vec->_data+vec->_size-i,                         \
               (_type*)vec->_data+vec->_size-1-i,                       \
               sizeof(_type));                                          \
    }   memcpy((_type*)vec->_data+index, data, sizeof(_type));          \

#define pop_back(vec, _type)                                            \
    get_ptr(vec, --vec->_size, _type)

#define erase(vec, index, _type)                                                \
    for(unsigned i=index; i<vec->_size-1; ++i){                                 \
        memcpy((_type*)vec->_data+i, (_type*)vec->_data+i+1, sizeof(_type));    \
    }   --vec->_size;

#define force_find(vec, data, _type, _result)                                   \
    {                                                                           \
        _type tmp = data;                                                       \
        _result = find(vec, &tmp, sizeof(_type))                                \
    }

#define exists(vec, data, _type, _result)                                       \
    force_find(vec, data, _type, _result)                                       \
    if(_result == -1){ _result = 0; }                                           \
    else{ _result = 1; }

#define swap(vec, index1, index2, _type)                                                \
    {                                                                                   \
        _type* tmp = malloc(sizeof(_type));                                             \
        memcpy(tmp, (_type*)vec->_data+index1, sizeof(_type));                          \
        memcpy((_type*)vec->_data+index1, (_type*)vec->_data+index2, sizeof(_type));    \
        memcpy(((_type*)vec->_data)+index2, tmp, sizeof(_type));                        \
        free((void*)tmp);                                                               \
    }

#define sort(vec, _sorter, _type)                                                   \
    for(unsigned i=0; i<vec->_size; ++i){                                           \
        for(unsigned j=0; j<vec->_size-1; ++j){                                     \
            if(_sorter(((_type*)vec->_data)[j], ((_type*)vec->_data)[j+1])){        \
                swap(vec, j, j+1, _type);                                           \
            }                                                                       \
        }                                                                           \
    }

#define apply_sort(vec, sorter) \
    sorter(vec->_data, vec->_size)

//
void __allocate(void** ptr, unsigned size, unsigned new_size);
// =======================

cvector* CVector(unsigned block_size, unsigned n_block);
unsigned size_of_cvector(const cvector* vec);
unsigned capacity_of_cvector(const cvector* vec);
void clear_cvector(cvector* vec);
void copy_cvector(cvector* dest, const cvector* src);
void deep_copy_vector(cvector* dest, const cvector* src);
unsigned find(const cvector* vec, const void* data, unsigned type_size);
void delete_cvector(cvector* vec);

#endif
