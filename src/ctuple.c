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
}

void CT_delete(ctuple* tuple){
    CV_delete_elements(&tuple->_elems);
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
    CV_push_back(&vec, element);
    CV_push_back(&tuple->_elems, &vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =