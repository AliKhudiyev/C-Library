
#ifndef _STRING_
#define _STRING_

#include "cvector.h"

typedef struct{
    cvector* _str;
}cstring;

cstring* CString(unsigned size);
void concat(cstring* str, const char* chars, unsigned size);
char compare(const cstring* str1, const cstring* str2, unsigned size);
void copy_cstring(cstring* dest, const cstring* src);
// void convert_to(const string* str, __Type type);
cstring* subcstring(const cstring* str, unsigned beg, unsigned end);
cstring* find_cstring(const cstring* str, const cstring* token, unsigned offset);
char get_char(const cstring* str, unsigned index);
const char* get_strptr(const cstring* str);
void delete_cstring(cstring* str);

#endif
