#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int age;
}Person;

int main(){

    cstring* str = CString(5);

    concat(str, (const char*)"Hello C-Library!\n", 0);
    concat(str, (const char*)"\tOk...\n", 0);

    cstring* str2 = CString(1);

    concat(str2, (const char*)"Hello ", 0);

    printf("%s\n--------------\n%s\n", get_strptr(str), get_strptr(str2));
    printf("comparison: %d\n", compare(str, str2, 0));
    printf("comparison: %d\n", compare(str2, str, 0));
    printf("comparison: %d\n", compare(str, str2, 6));
    printf("comparison: %d\n", compare(str, str2, 7));

    printf("%u\n", str->_str->_size);
    printf("%u\n", str2->_str->_size);

    return 0;
}