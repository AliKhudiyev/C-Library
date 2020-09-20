
#ifndef _DICTIONARY_
#define _DICTIONARY_

#include "cvector.h"

typedef struct{
    cvector* _key;
    cvector** _values;
}cdictionary;

cdictionary* CDictionary();
void add_pair(cdictionary* dict, const cvector* key, const cvector* values);
unsigned find_key(const cdictionary* dict, const cvector* key);
void delete_cdictionary(cdictionary* dict);

#endif
