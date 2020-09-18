
#ifndef _DICTIONARY_
#define _DICTIONARY_

#include "cvector.h"

typedef struct{
    cvector _key;
    cvector* _values;
}cdictionary;

cdictionary* CDictionary();
void delete_cdictionary(cdictionary* dict);

#endif
