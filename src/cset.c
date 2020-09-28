#include "cset.h"

// Constructor and Destructor
cset* CSet(size_t block_size, size_t n_block){
    ;
}

void CSet_init(cset* set, size_t block_size, size_t n_block){
    ;
}

void CSet_delete(cset* set){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void* CSet_begin(const cset* set){
    ;
}

void* CSet_end(const cset* set){
    ;
}

const void* CSet_cbegin(const cset* set){
    ;
}

const void* CSet_cend(const cset* set){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
bool_t CSet_empty(const cset* set){
    ;
}

size_t CSet_size(const cset* set){
    ;
}

size_t CSet_max_size(const cset* set){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CSet_insert(cset* set, const void* element){
    ;
}

void CSet_erase(cset* set, const void* element){
    ;
}

void CSet_swap(cset* set1, cset* set2){
    ;
}

void CSet_clear(cset* set){
    ;
}

#define MCSet_emplace(set, _type, ...)          \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CSet_insert(set, (const void*)&tmp);    \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

// Operations
size_t CSet_find(const cset* set, const void* element){
    ;
}

size_t CSet_count(const cset* set, const void* element){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
// = = = = = = = = = = = = = = = = = = = = = = =