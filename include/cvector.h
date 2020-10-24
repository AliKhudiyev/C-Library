
#ifndef _VECTOR_
#define _VECTOR_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

#include "ctypes.h"

typedef struct{
    size_t _size, _capacity, _block_size;
    void* _data;
    void (*_copy)(void* _dest, const void* _src, size_t _n_byte);
    void (*_delete)(void* _ptr);
    const char* (*_str)(void* _data);
}cvector;

// Allocator
void __allocate(void** ptr, size_t size, size_t new_size);

#define __vallocate(ptr, size, new_size, _type, ...)                        \
    __allocate(ptr, size, new_size);                                        \
    if(*(ptr)){                                                             \
        _type tmp = __VA_ARGS__;                                            \
        for(size_t i=0; i<(new_size)/sizeof(_type); ++i){                   \
            memcpy(((_type*)*(ptr))+i, &tmp, sizeof(_type));                \
        }                                                                   \
    }
    
// = = = = = = = = = = = = = = = = = = = = = = =

// Constructor and Destructor
cvector* CVector(size_t block_size, size_t n_block);
void CV_init(cvector* vec, size_t block_size, size_t n_block);
void CV_delete(cvector* vec);
void CV_delete_elements(cvector* vec);
void CV_delete_recursive(void* vec);
void CV_destruct(void* vec);

#define MCVector(_type, size)                                   \
    CVector(sizeof(_type), size);

#define MCV_init(vec, _type, size)                              \
    cvector vec;                                                \
    CV_init(&vec, sizeof(_type), size);
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void* CV_begin(const cvector* vec);
void* CV_end(const cvector* vec);
const void* CV_cbegin(const cvector* vec);
const void* CV_cend(const cvector* vec);

#define MCV_begin(vec, _type)                                               \
    (_type*)CV_begin(vec);

#define MCV_end(vec, _type)                                                 \
    (_type*)CV_end(vec);

#define MCV_cbegin(vec, _type)                                              \
    (const _type*)CV_cbegin(vec);

#define MCV_cend(vec, _type)                                                \
    (const _type*)CV_cend(vec);
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
size_t CV_size(const cvector* vec);
void CV_resize(cvector* vec, size_t n);
size_t CV_capacity(const cvector* vec);
bool_t CV_empty(const cvector* vec);
void CV_shrink_to_fit(cvector* vec);
size_t CV_block_size(const cvector* vec);
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CV_at(const cvector* vec, size_t position);
void* CV_front(const cvector* vec);
void* CV_back(const cvector* vec);
void* CV_data(const cvector* vec);

#define MCV_at(vec, position, _type) \
    ((_type*)(position < (vec)->_size? (_type*)(vec)->_data+position : NULL))

#define MCV_front(vec, _type) \
    MCV_at((vec), 0, _type)

#define MCV_back(vec, _type) \
    MCV_at((vec), (vec)->_size-1, _type)

// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CV_assign(cvector* vec1, const cvector* vec2, size_t pos, size_t size);
void CV_push_back(cvector* vec, const void* val);
void CV_pop_back(cvector* vec);
void CV_insert(cvector* vec, size_t position, const void* val);
void CV_erase(cvector* vec, size_t position);
void CV_swap(cvector* vec1, cvector* vec2);
void CV_clear(cvector* vec);

#define MCV_force_push_back(vec, val, _type)                                \
    {                                                                       \
        _type tmp = val;                                                    \
        CV_push_back(vec, (const void*)&tmp);                                            \
    }

#define MCV_force_insert(vec, position, val, _type)                         \
    {                                                                       \
        _type tmp = val;                                                    \
        CV_insert(vec, position, (const void*)&tmp);                                     \
    }

#define MCV_emplace(vec, position, _type, ...)                              \
    {                                                                       \
        _type tmp = { __VA_ARGS__ };                                        \
        CV_insert(vec, position, &tmp);                                     \
    }

#define MCV_emplace_back(vec, _type, ...)                                   \
    {                                                                       \
        _type tmp = { __VA_ARGS__ };                                        \
        CV_push_back(vec, &tmp);                                            \
    }

#define MCV_force_emplace(vec, position, _type, _constructor, ...)          \
    {                                                                       \
        _type tmp;                                                          \
        _constructor( &tmp, __VA_ARGS__ );                                  \
        CV_insert(vec, position, &tmp);                                     \
    }

#define MCV_force_emplace_back(vec, _type, _constructor, ...)               \
    {                                                                       \
        _type tmp;                                                          \
        _constructor( &tmp, __VA_ARGS__ );                                  \
        CV_push_back(vec, &tmp);                                            \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CV_enlarge(cvector* vec, size_t n);
void CV_set_destructor(cvector* vec, void (*destructor)(void*));
void CV_set_deep_copy(cvector* vec, void (*copy)(void* dest, const void* src, size_t n_byte));
void CV_swap_val(cvector* vec, size_t pos1, size_t pos2);
void CV_copy(cvector* dest, const cvector* src);
void CV_deep_copy(cvector* dest, const cvector* src);
size_t CV_find(const cvector* vec, const void* val);
void CV_set_printer(cvector* vec, f_printer_t printer);

#define MCV_force_find(vec, data, _type, _result)                            \
    {                                                                        \
        _type tmp = data;                                                    \
        _result = CV_find(vec, &tmp);                                        \
    }

#define MCV_sort(vec, _sorter, _type)                                               \
    for(unsigned i=0; i<vec->_size; ++i){                                           \
        for(unsigned j=0; j<vec->_size-1; ++j){                                     \
            if(_sorter(((_type*)vec->_data)[j], ((_type*)vec->_data)[j+1])){        \
                CV_swap_val(vec, j, j+1);                                       \
            }                                                                       \
        }                                                                           \
    }

#define MCV_apply_sort(vec, sorter) \
    sorter(vec->_data, vec->_size)

#define MCV_apply(function) \
    function(vec->_data, vec->_size, vec->_capacity, vec->_block_size)

#define MCV_For_Each(vec, iterator, ...)                        \
    for(size_t i=0; i<CV_size(vec); ++i){                       \
        iterator=CV_at(vec, i);                                 \
        __VA_ARGS__                                             \
    }

#define MCV_Enumerate(vec, counter, iterator, ...)              \
    for(counter=0; counter<CV_size(vec); ++counter){            \
        iterator=CV_at(vec, counter);                           \
        __VA_ARGS__                                             \
    }

#define MCV_to_str(vec, _type)

#define MCV_str(vec, position)   \
    ((const char*)((vec)->_str? (vec)->_str(CV_at(vec, position)) : NULL))
// = = = = = = = = = = = = = = = = = = = = = = =

extern char* CPrinter_get_buffer();
extern void CPrinter_set_buffer(const char*, size_t);
extern void CPrinter_delete();

#endif
