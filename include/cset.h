
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
// = = = = = = = = = = = = = = = = = = = = = = =

// Operations
size_t CSet_find(const cset* set, const void* element);
size_t CSet_count(const cset* set, const void* element);
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
// = = = = = = = = = = = = = = = = = = = = = = =

#endif
