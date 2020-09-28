
#ifndef _TUPLE_
#define _TUPLE_

#include "cvector.h"

typedef struct{
    cvector _elems;
}ctuple;

// Constructor and Destructor
ctuple* CTuple();
void CT_init(ctuple* tuple);
void CT_delete(ctuple* tuple);
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CT_swap(ctuple* tuple1, ctuple* tuple2);
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
#define CT_get(tuple, position, _type)  \
    MCV_front(MCV_at(&(tuple)->_elems, position, cvector), _type)
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CT_add(ctuple* tuple, const void* element, size_t size);

#define MCT_force_add(tuple, _type, ...)         \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CT_add(tuple, &tmp, sizeof(_type));     \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

#endif
