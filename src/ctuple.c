#include "ctuple.h"

// Constructor and Destructor
ctuple* CTuple(){
    ctuple* tuple = NULL;

    __allocate((void**)&tuple, 0, sizeof(ctuple));
    CT_init(tuple);

    return tuple;
}

void CT_init(ctuple* tuple){
    CV_init(&tuple->_elems, sizeof(cvector), 1);
    CV_set_destructor(&tuple->_elems, CV_delete_recursive);
}

void CT_delete(ctuple* tuple){
    CV_delete_elements(&tuple->_elems);
    CV_delete(&tuple->_elems);
    // TO DO: Check if the function works!
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CT_swap(ctuple* tuple1, ctuple* tuple2){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CT_add(ctuple* tuple, const void* element, size_t size){
    cvector vec;
    
    CV_init(&vec, size, 1);
    // CV_set_destructor(&vec, CV_delete_recursive);
    CV_push_back(&vec, element);
    CV_push_back(&tuple->_elems, &vec);
}

size_t CT_find(const ctuple* tuple, const void* element, size_t size){
    for(size_t i=0; i<CT_size(tuple); ++i){
        if(CV_block_size((cvector*)CV_at(&tuple->_elems, i)) != size) continue;
        if(!memcmp(CV_data(MCV_at(&tuple->_elems, i, cvector)), element, size)) return i;
    }
    return -1;
}

size_t CT_size(const ctuple* tuple){
    return CV_size(&tuple->_elems);
}
// = = = = = = = = = = = = = = = = = = = = = = =