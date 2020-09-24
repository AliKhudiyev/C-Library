#include "cset.h"

cset* CSet(unsigned block_size){
    cset* set;
    __allocate((void**)&set, 0, sizeof(cset));

    set->_elems = CVector(block_size, 1);

    return set;
}

bool_t CSet_exists(const cset* set, const void* element){
    return CV_find(set->_elems, element) == -1? False : True;
}

bool_t CSet_add(cset* set, const void* element){
    if(CSet_exists(set, element)) return False;
    CV_push_back(set->_elems, element);
    return True;
}

void CSet_delete(cset* set){
    CV_delete(set->_elems);
    free((void*)set);
}