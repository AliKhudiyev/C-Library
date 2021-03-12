#include "cset.h"
#include <stdio.h>

// Constructor and Destructor
cset* CSet(size_t block_size, size_t n_block){
    cset* set = NULL;

    __allocate((void**)&set, 0, sizeof(cset));
    CSet_init(set, block_size, n_block);

    return set;
}

void CSet_init(cset* set, size_t block_size, size_t n_block){
    CV_init(&set->_elems, block_size, n_block);
}

void CSet_delete(cset* set){
    CV_destruct(&set->_elems);

    CPrinter_delete();
}

void CSet_destruct(void* set){
    CSet_delete((cset*)set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void* CSet_begin(const cset* set){
    return CV_begin(&set->_elems);
}

void* CSet_end(const cset* set){
    return CV_end(&set->_elems);
}

const void* CSet_cbegin(const cset* set){
    return CV_cbegin(&set->_elems);
}

const void* CSet_cend(const cset* set){
    return CV_end(&set->_elems);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
bool_t CSet_empty(const cset* set){
    return CV_empty(&set->_elems);
}

size_t CSet_size(const cset* set){
    return CV_size(&set->_elems);
}

size_t CSet_max_size(const cset* set){
    return CV_capacity(&set->_elems);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CSet_at(const cset* set, size_t position){
    if(position >= CSet_size(set)) return NULL;
    return CV_at(&set->_elems, position);
}

void* CSet_front(const cset* set){
    return CSet_at(set, 0);
}

void* CSet_back(const cset* set){
    return CSet_at(set, CSet_size(set)-1);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CSet_insert(cset* set, const void* element){
    if(CSet_count(set, element)) return ;

    CV_push_back(&set->_elems, element);
}

void CSet_erase(cset* set, const void* element){
    if(!CSet_count((const cset*)set, element)) return ;

    size_t position = CSet_find(set, element);
    CV_erase(&set->_elems, position);
}

void CSet_swap(cset* set1, cset* set2){
    CV_swap(&set1->_elems, &set2->_elems);
}

void CSet_clear(cset* set){
    CV_clear(&set->_elems);
}

#define MCSet_emplace(set, _type, ...)          \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CSet_insert(set, (const void*)&tmp);    \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

// Operations
size_t CSet_find(const cset* set, const void* element){
    return CV_find(&set->_elems, element);
}

size_t CSet_count(const cset* set, const void* element){
    return CSet_find(set, element) == -1? False : True;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CSet_set_deep_copy(cset* set, f_copy_t copy){
    CV_set_deep_copy(&set->_elems, copy);
}

void CSet_set_destructor(cset* set, f_destructor_t destructor){
    CV_set_destructor(&set->_elems, destructor);
}
// = = = = = = = = = = = = = = = = = = = = = = =