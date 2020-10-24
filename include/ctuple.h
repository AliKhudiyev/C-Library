
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
void CT_destruct(void* tuple);
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CT_swap(ctuple* tuple1, ctuple* tuple2);
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void* CT_at(const ctuple* tuple, size_t position);
void* CT_front(const ctuple* tuple, size_t position);
void* CT_back(const ctuple* tuple, size_t position);

#define MCT_at(tuple, position, _type)      \
    ((_type*)CT_at(tuple, position))

#define MCT_front(tuple, _type)             \
    MCT_at(tuple, 0, _type)

#define MCT_back(tuple, _type)              \
    MCT_at(tuple, CT_size(tuple)-1, _type)
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void CT_add(ctuple* tuple, const void* element, size_t size);
size_t CT_find(const ctuple* tuple, const void* element, size_t size);
size_t CT_size(const ctuple* tuple);
void CT_set_destructor(ctuple* tuple, size_t position, void (*destuctor)(void* ptr));

#define MCT_force_add(tuple, _type, ...)        \
    {                                           \
        _type tmp = { __VA_ARGS__ };            \
        CT_add(tuple, &tmp, sizeof(_type));     \
    }

#define MCT_force_find(_result, tuple, _type, ...)      \
    {                                                   \
        _type tmp = { __VA_ARGS__ };                    \
        _result = CT_find(tuple, &tmp, sizeof(_type));  \
    }

#define MCT_For_Each(tuple, iterator, ...)                      \
    for(size_t i=0; i<CT_size(tuple); ++i){                     \
        iterator=CT_at(tuple, i);                               \
        __VA_ARGS__                                             \
    }

#define MCT_Enumerate(tuple, counter, iterator, ...)            \
    for(counter=0; counter<CT_size(tuple); ++counter){          \
        iterator=CT_at(tuple, counter);                         \
        __VA_ARGS__                                             \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

#endif
