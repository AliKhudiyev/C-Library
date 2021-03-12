
#ifndef _SET_
#define _SET_

#include "cvector.h"

typedef struct{
    cvector _elems;
}cset;

// Constructor and Destructor
cset* CSet(size_t block_size, size_t n_block);
void CSet_init(cset* set, size_t block_size, size_t n_block);
void CSet_delete(cset* set);
void CSet_destruct(void* set);

#define MCSet(_type)                    \
    CSet(sizeof(_type), 1);

#define MCSet_init(set, _type)          \
    cset set;                           \
    CSet_init(&set, sizeof(_type), 1);
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void* CSet_begin(const cset* set);
void* CSet_end(const cset* set);
const void* CSet_cbegin(const cset* set);
const void* CSet_cend(const cset* set);
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
bool_t CSet_empty(const cset* set);
size_t CSet_size(const cset* set);
size_t CSet_max_size(const cset* set);
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CSet_at(const cset* set, size_t position);
void* CSet_front(const cset* set);
void* CSet_back(const cset* set);

#define MCSet_at(set, position, _type)  \
    ((_type*)CSet_at(set, position))

#define MCSet_front(set, _type) \
    ((_type*)CSet_front(set))

#define MCSet_back(set, _type)  \
    ((_type*)CSet_back(set))
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CSet_insert(cset* set, const void* element);
void CSet_erase(cset* set, const void* element);
void CSet_swap(cset* set1, cset* set2);
void CSet_clear(cset* set);

#define MCSet_emplace(set, _type, ...)          \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CSet_insert(set, (const void*)&tmp);    \
    }

#define MCSet_force_erase(set, _type, ...)      \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CSet_erase(set, (const void*)&tmp);     \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

// Operations
size_t CSet_find(const cset* set, const void* element);
size_t CSet_count(const cset* set, const void* element);

#define MCSet_force_find(set, result, _type, ...)   \
    {                                               \
        _type tmp = { __VA_ARGS__ };                \
        result = CSet_find(set, &tmp);              \
    }

#define MCSet_force_count(set, result, _type, ...)  \
    {                                               \
        _type tmp = { __VA_ARGS__ };                \
        result = CSet_count(set, &tmp);             \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CSet_set_deep_copy(cset* set, f_copy_t copy);
void CSet_set_destructor(cset* set, f_destructor_t destructor);

#define MCSet_For_Each(set, iterator, ...)                                    \
    for(size_t i=0; i<CSet_size(set); ++i){                                   \
        iterator=CSet_at(set, i);                                             \
        __VA_ARGS__                                                           \
    }

#define MCSet_Enumerate(set, counter, iterator, ...)                          \
    for(counter=0; counter<CV_size(set); ++counter){                          \
        iterator=CSet_at(set, counter);                                       \
        __VA_ARGS__                                                           \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

#endif
