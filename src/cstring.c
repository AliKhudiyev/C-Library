#include "cstring.h"
#include <stdio.h>

void __CS_append_null_char(cstring* str){
    MCV_force_push_back(&str->_str, '\0', char);
}

// Constructor and Destructor
cstring* CString(size_t size){
    cstring* str = NULL;

    __allocate((void**)&str, 0, sizeof(cstring));
    CS_init(str, size);

    return str;
}

void CS_init(cstring* str, size_t size){
    CV_init(&str->_str, sizeof(char), size);
    // str->_str._delete = CV_delete_recursive;
}

void CS_delete(cstring* str){
    CV_delete(&str->_str);
    
    CPrinter_delete();
}

void CS_destruct(void* str){
    CS_delete((cstring*)str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
char* CS_begin(const cstring* str){
    return MCV_begin(&str->_str, char);
}

char* CS_end(const cstring* str){
    return MCV_end(&str->_str, char);
}

const char* CS_cbegin(const cstring* str){
    return MCV_cbegin(&str->_str, char);
}

const char* CS_cend(const cstring* str){
    return MCV_cend(&str->_str, char);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
size_t CS_size(const cstring* str){
    return CV_size(&str->_str);
}

void CS_resize(cstring* str, size_t n){
    CV_resize(&str->_str, n);
}

size_t CS_capacity(const cstring* str){
    return CV_capacity(&str->_str);
}

// void CS_reserve(cstring* str){
//     // TO DO
// }

void CS_clear(cstring* str){
    CV_clear(&str->_str);
}

bool_t CS_empty(const cstring* str){
    return CV_empty(&str->_str);
}

void CS_shrink_to_fit(cstring* str){
    CV_shrink_to_fit(&str->_str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
char CS_at(const cstring* str, size_t position){
    if(position >= CS_size(str)) return 0;
    return *(CS_cbegin(str)+position);
}

char CS_front(const cstring* str){
    return CS_at(str, 0);
}

char CS_back(const cstring* str){
    return CS_at(str, CS_size(str)-1);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void CS_append(cstring* str, const char* chars, size_t size){
    size_t sz = (size <= strlen(chars)? size : strlen(chars));
    
    for(unsigned i=0; i<sz; ++i){
        CS_push_back(str, chars[i]);
    }
}

void CS_push_back(cstring* str, char c){
    size_t size = CS_size(str);
    /* - - - - - - - - - - - - - - */
    if(size && !CS_at(str, size-1)){
        CV_erase(&str->_str, size-1);
    }
    CV_push_back(&str->_str, &c);
    __CS_append_null_char(str);
    /* - - - - - - - - - - - - - - */
    // Better solution: CV_insert(&str->_str, size-1, &c);
}

void CS_assign(cstring* str, const char* chars, size_t size){
    if(size == -1) size = strlen(chars);

    cstring str2;
    CS_init(&str2, size);
    CS_append(&str2, chars, size);
    CV_copy(&str->_str, &str2._str);
    CS_delete(&str2);
}

void CS_insert(cstring* str, size_t position, const char* chars, size_t n){
    if(n > strlen(chars)) n = strlen(chars);
    if(position > CS_size(str)) return ;

    for(size_t i=0; i<n; ++i){
        CV_insert(&str->_str, position+i, chars+i);
    }
    // TO DO: Optimize this function!
}

void CS_erase(cstring* str, size_t position){
    if(position != -1 && position + 1 == CS_size(str)){
       fprintf(stderr, "%s", "WARNING[CS_erase]: Erasing \\0 from string!");
    }
    CV_erase(&str->_str, position);
}

void CS_replace(cstring* str, size_t position, size_t size, const char* chars){
    if(size == -1) size = CS_size(str) - position;
    if(position >= CS_size(str) || position + size > CS_size(str)) return ;

    for(size_t i=0; i<size; ++i){
        CS_erase(str, position);
    }   CS_insert(str, position, chars, strlen(chars));
    // TO DO: Optimize this function!
}

void CS_swap(cstring* str1, cstring* str2){
    CV_swap(&str1->_str, &str2->_str);
}

void CS_pop_back(cstring* str){
    CV_erase(&str->_str, CS_size(str)-2);
    // CV_pop_back(&str->_str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// String operations
const char* CS_c_str(const cstring* str){
    return (CS_size(str)? (const char*)str->_str._data : NULL);
}

void* CS_data(const cstring* str){
    return CV_data(&str->_str);
}

void CS_copy(cstring* str, char* buffer, size_t size, size_t position){
    if(position >= CS_size(str) || position + size > CS_size(str)) return ;
    
    memcpy((void*)buffer, CS_c_str(str)+position, size);
}

size_t CS_find(const cstring* str, const char* chars, size_t position){
    if(position >= CS_size(str)) return -1;

    return CAlgo_find((const void*)CV_data(&str->_str), 
                      CS_size(str), 
                      sizeof(char), 
                      chars, 
                      position, 
                      CS_size(str),
                      NULL);
}

size_t CS_rfind(const cstring* str, const char* chars, size_t position){
    return CAlgo_rfind((const void*)CV_data(&str->_str), 
                        CS_size(str), 
                        sizeof(char), 
                        chars, 
                        position, 
                        CS_size(str),
                        NULL);
}

size_t CS_find_first_of(const cstring* str, const char* chars, size_t position){
    return CAlgo_find_first_of((const void*)CV_data(&str->_str), 
                                CS_size(str), 
                                sizeof(char), 
                                chars, 
                                position, 
                                CS_size(str),
                                NULL);
}

size_t CS_find_last_of(const cstring* str, const char* chars, size_t position){
    return CAlgo_find_last_of((const void*)CV_data(&str->_str), 
                               CS_size(str), 
                               sizeof(char), 
                               chars, 
                               position, 
                               CS_size(str),
                               NULL);
}

size_t CS_find_first_not_of(const cstring* str, const char* chars, size_t position){
    return CAlgo_find_first_not_of((const void*)CV_data(&str->_str), 
                                    CS_size(str), 
                                    sizeof(char), 
                                    chars, 
                                    position, 
                                    CS_size(str),
                                    NULL);
}

size_t CS_find_last_not_of(const cstring* str, const char* chars, size_t position){
    return CAlgo_find_last_not_of((const void*)CV_data(&str->_str), 
                                   CS_size(str), 
                                   sizeof(char), 
                                   chars, 
                                   position, 
                                   CS_size(str),
                                   NULL);
}

cstring* CS_substr(const cstring* str, size_t position, size_t size){
    if(position < CS_size(str) && size == -1) size = CS_size(str) - position;
    if(position >= CS_size(str) || position + size > CS_size(str)) return NULL;

    cstring* string = CString(size);
    CS_append(string, CS_c_str(str)+position, size);

    return string;
}

char CS_compare(const cstring* str1, const cstring* str2, unsigned size){
    size_t sz1 = CS_size(str1), sz2 = CS_size(str2);
    size_t sz = (size <= sz1? (size <= sz2? size : sz2) : (sz1 <= sz2? sz1 : sz2));
    
    if(size == -1){
        if(sz1 < sz2){
            return -1;
        } else if(sz1 > sz2){
            return 1;
        } else{
            for(size_t i=0; i<sz1; ++i){
                if(CS_at(str1, i) < CS_at(str2, i)) return -1;
                if(CS_at(str1, i) > CS_at(str2, i)) return 1;
            }
            return 0;
        }
    }

    for(size_t i=0; i<sz; ++i){
        if(CS_at(str1, i) < CS_at(str2, i)) return -1;
        if(CS_at(str1, i) > CS_at(str2, i)) return 1;
    }

    return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
// = = = = = = = = = = = = = = = = = = = = = = =

