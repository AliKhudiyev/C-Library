
#ifndef _PAIR_
#define _PAIR_

#include "cvector.h"

typedef struct{
    unsigned _key_size;

    void* _key;
    cvector* _values;
}cpair;

#define force_make_pair(pair, key, values, _type_key)   \
    {   \
        _type_key tmp = key;    \
        make_pair(pair, &tmp, values);  \
    }

#define get_firstptr(pair, _type)    \
    (_type*)pair->_key

#define get_secondptr(pair, index, _type) \
    (_type*) (index < pair->_values->_size? (_type*)pair->_values->_data+index : NULL)

cpair* CPair(unsigned key_size, unsigned value_size);
void make_pair(cpair* pair, const void* key, const cvector* values);
void set_key(cpair* pair, const void* key);
void set_value(cpair* pair, const void* value, unsigned index);
void add_value(cpair* pair, const void* value);
unsigned size_of_values(const cpair* pair);
void delete_pair(cpair* pair);

#endif
