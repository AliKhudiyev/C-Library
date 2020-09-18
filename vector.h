
#ifndef _VECTOR_
#define _VECTOR_

#include "type.h"

typedef struct{
    unsigned _size, _capacity, _block_size;
    void* _data;
}vector;

#define push_back(vec, data, _type)                                     \
    if(vec->_size >= vec->_capacity){                                   \
        vec->_capacity *= 2;                                            \
        allocate(&vec->_data,                                           \
                 vec->_capacity*vec->_block_size/2,                     \
                 vec->_capacity*vec->_block_size);                      \
    }   memcpy((_type*)vec->_data+vec->_size++, data, sizeof(_type));

#define get_ptr(vec, index, _type)                                      \
    ((_type*)(index < vec->_size? (_type*)vec->_data+index : NULL))

#define enlarge(vec, n, _type)                                          \
    if(vec->_size+n-1 >= vec->_capacity){                               \
        vec->_capacity += n;                                            \
        allocate(&vec->_data,                                           \
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

#define erase(vec, index, _type)                                        \
    for(unsigned i=index; i<vec->_size-1; ++i){\
        memcpy((_type*)vec->_data+i, (_type*)vec->_data+i+1, sizeof(_type));\
    }   --vec->_size;

//
void allocate(void** ptr, unsigned size, unsigned new_size);
// =======================

vector* Vector(unsigned size, unsigned n_block);
unsigned size_of(const vector* vec);
unsigned capacity_of(const vector* vec);
void clear(vector* vec);
void delete_vector(vector* vec);

#endif
