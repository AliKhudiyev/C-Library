
#ifndef _SET_
#define _SET_

#include "cvector.h"

typedef struct{
    cvector* _elems;
}cset;

#define add_element(set, data, _type)                           \
    {                                                           \
        bool_t result;                                          \
        exists(set->_elems, data, _type, result);               \
        if(!result){ push_back(set->_elems, data, _type); }     \
    }

#define get_valptr(set, index, _type)                           \
    get_ptr(set->_elems, index, _type)

#define get_vptr(set)                                           \
    set->_elems;

#define force_find_element(set, element, _type, _result)        \
        force_find(set->_elems, element, _type, _result)

cset* CSet();
// bool_t add_element(cset* set, void*);
void free_cset(cset* set);

#endif
