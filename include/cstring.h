
#ifndef _STRING_
#define _STRING_

#include "cvector.h"

typedef struct{
    cvector* _str;
}cstring;

cstring* CString(unsigned size);
void CS_concat(cstring* str, const char* chars, unsigned size);
char CS_compare(const cstring* str1, const cstring* str2, unsigned size);
void CS_copy(cstring* dest, const cstring* src);
// void convert_to(const string* str, __Type type);
cstring* CS_subcstring(const cstring* str, unsigned beg, unsigned end);
cstring* CS_find(const cstring* str, const cstring* token, unsigned offset);
char CS_get_char(const cstring* str, unsigned index);
const char* CS_get_strptr(const cstring* str);
void CS_delete(cstring* str);

#endif
