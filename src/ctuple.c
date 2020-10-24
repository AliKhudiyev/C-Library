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
    CV_destruct(&tuple->_elems);

    CPrinter_delete();
}

void CT_destruct(void* tuple){
    CT_delete((ctuple*)tuple);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CT_swap(ctuple* tuple1, ctuple* tuple2){
    CV_swap(&tuple1->_elems, &tuple2->_elems);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CT_at(const ctuple* tuple, size_t position){
    if(position >= CT_size(tuple)) return NULL;

    return CV_front(CV_at(&tuple->_elems, position));
}

void* CT_front(const ctuple* tuple, size_t position){
    return CT_at(tuple, 0);
}

void* CT_back(const ctuple* tuple, size_t position){
    return CT_at(tuple, CT_size(tuple)-1);
}
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

void CT_set_destructor(ctuple* tuple, size_t position, void (*destuctor)(void* ptr)){
    if(position >= CV_size(&tuple->_elems)) return ;

    CV_set_destructor(CV_at(&tuple->_elems, position), destuctor);
}
// = = = = = = = = = = = = = = = = = = = = = = =