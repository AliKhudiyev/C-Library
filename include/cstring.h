
#ifndef _STRING_
#define _STRING_

#include "cvector.h"

typedef struct{
    cvector _str;
}cstring;

// Constructor and Destructor
cstring* CString(size_t size);
void CS_init(cstring* str, size_t size);
void CS_delete(cstring* str);
void CS_destruct(void* str);

#define MCString(size)      \
    CString(size);

#define MCS_init(str)       \
    cstring str;            \
    CS_init(&str, 0);
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
char* CS_begin(const cstring* str);
char* CS_end(const cstring* str);
const char* CS_cbegin(const cstring* str);
const char* CS_cend(const cstring* str);
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
size_t CS_size(const cstring* str);
void CS_resize(cstring* str, size_t n);
size_t CS_capacity(const cstring* str);
// void CS_reserve(cstring* str);
void CS_clear(cstring* str);
bool_t CS_empty(const cstring* str);
void CS_shrink_to_fit(cstring* str);
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
char CS_at(const cstring* str, size_t position);
char CS_front(const cstring* str);
char CS_back(const cstring* str);
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CS_append(cstring* str, const char* chars, size_t size);
void CS_push_back(cstring* str, char c);
void CS_assign(cstring* str, const char* chars, size_t size);
void CS_insert(cstring* str, size_t position, const char* chars, size_t n);
void CS_erase(cstring* str, size_t position);
void CS_replace(cstring* str, size_t position, size_t size, const char* chars);
void CS_swap(cstring* str1, cstring* str2);
void CS_pop_back(cstring* str);
// = = = = = = = = = = = = = = = = = = = = = = =

// String operations
const char* CS_c_str(const cstring* str);
void* CS_data(const cstring* str);
void CS_copy(cstring* str, char* buffer, size_t size, size_t position);
size_t CS_find(const cstring* str, const char* chars, size_t position);
size_t CS_rfind(const cstring* str, const char* chars, size_t position);
size_t CS_find_first_of(const cstring* str, const char* chars, size_t position);
size_t CS_find_last_of(const cstring* str, const char* chars, size_t position);
size_t CS_find_first_not_of(const cstring* str, const char* chars, size_t position);
size_t CS_find_last_not_of(const cstring* str, const char* chars, size_t position);
cstring* CS_substr(const cstring* str, size_t position, size_t size);
char CS_compare(const cstring* str1, const cstring* str2, unsigned size);
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
#define MCS_For_Each(str, iterator, ...)                        \
    for(size_t i=0; i<CS_size(str); ++i){                       \
        iterator=CS_at(str, i);                                 \
        __VA_ARGS__                                             \
    }

#define MCS_Enumerate(str, counter, iterator, ...)              \
    for(counter=0; counter<CS_size(str); ++counter){            \
        iterator=CS_at(str, counter);                           \
        __VA_ARGS__                                             \
    }
// = = = = = = = = = = = = = = = = = = = = = = =

#endif
