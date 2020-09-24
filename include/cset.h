
#ifndef _SET_
#define _SET_

#include "cvector.h"

typedef struct{
    cvector* _elems;
}cset;

#define MCSet_add(set, data, _type)                           \
    {                                                           \
        bool_t result;                                          \
        exists(set->_elems, data, _type, result);               \
        if(!result){ push_back(set->_elems, data, _type); }     \
    }

#define MCSet_get_valptr(set, index, _type)                           \
    get_ptr(set->_elems, index, _type)

#define MCSet_get_vptr(set)                                           \
    set->_elems;

#define MCSet_force_find(set, element, _type, _result)        \
        force_find(set->_elems, element, _type, _result)

cset* CSet(unsigned block_size);
bool_t CSet_exists(const cset* set, const void* element);
bool_t CSet_add(cset* set, const void* element);
void CSet_free(cset* set);

#endif
