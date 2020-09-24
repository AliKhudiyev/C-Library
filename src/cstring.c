#include "cstring.h"
#include <stdio.h>

cstring* CString(unsigned size){
    cstring* str = malloc(sizeof(cstring));
    str->_str = CVector(sizeof(char), size);
    return str;
}

void CS_concat(cstring* str, const char* chars, unsigned size){
    unsigned sz = size? size : strlen(chars);
    
    if(str->_str->_size){
        MCV_erase(str->_str, str->_str->_size-1, char);
    }
    for(unsigned i=0; i<sz; ++i){
        MCV_push_back(str->_str, chars+i, char);
    }   MCV_push_back(str->_str, "\0", char);
}

char CS_compare(const cstring* str1, const cstring* str2, unsigned size){
    unsigned sz = size<=str1->_str->_size? size : str1->_str->_size;

    if(!size){
        sz = str1->_str->_size;
        if(str1->_str->_size > str2->_str->_size) return 1;
        else if(str1->_str->_size < str2->_str->_size) return -1;
    } else if(size > str1->_str->_size || size > str2->_str->_size){
        if(str1->_str->_size > str2->_str->_size) return 1;
        else if(str1->_str->_size < str2->_str->_size) return -1;
    }

    for(unsigned i=0; i<sz; ++i){
        if(*MCV_get_ptr(str1->_str, i, char) > *MCV_get_ptr(str2->_str, i, char)){
            return 1;
        }
        if(*MCV_get_ptr(str1->_str, i, char) < *MCV_get_ptr(str2->_str, i, char)){
            return -1;
        }
    }
    return 0;
}

void CS_copy(cstring* dest, const cstring* src){
    CV_copy(dest->_str, src->_str);
}

// void convert_to(const string* str, __Type type);

cstring* CS_substring(const cstring* str, unsigned beg, unsigned end){
    return 0;
}

cstring* CS_find(const cstring* str, const cstring* token, unsigned offset){
    return 0;
}

char CS_get_char(const cstring* str, unsigned index){
    return (char)*MCV_get_ptr(str->_str, index, char);
}

const char* CS_get_strptr(const cstring* str){
    return (const char*)str->_str->_data;
}

void CS_delete(cstring* str){
    CV_delete(str->_str);
    free((void*)str);
    str = NULL;
}