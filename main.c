#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int age;
}Person;

bool_t my_sorter(int a, int b){
    return a >= b;
}

int main(){

    cvector* v1 = CVector(sizeof(int), 1);
    cvector* v2 = CVector(sizeof(int), 3);

    force_push_back(v1, 1, int);
    force_push_back(v1, 2, int);

    for(int i=0; i<20; ++i){
        force_push_back(v2, rand()%20, int);
    }

    printf("size: %u - %u\n", size_of_cvector(v1), size_of_cvector(v2));
    for(int i=0; i<size_of_cvector(v1); ++i){
        printf("%d ", *get_ptr(v1, i, int));
    }   printf("\n");
    for(int i=0; i<size_of_cvector(v2); ++i){
        printf("%d ", *get_ptr(v2, i, int));
    }   printf("\n");

    copy_cvector(v1, v2);

    printf("size: %u - %u\n", size_of_cvector(v1), size_of_cvector(v2));
    for(int i=0; i<size_of_cvector(v1); ++i){
        printf("%d ", *get_ptr(v1, i, int));
    }   printf("\n");
    for(int i=0; i<size_of_cvector(v2); ++i){
        printf("%d ", *get_ptr(v2, i, int));
    }   printf("\n");

    sort(v1, my_sorter, int);

    printf("size: %u - %u\n", size_of_cvector(v1), size_of_cvector(v2));
    for(int i=0; i<size_of_cvector(v1); ++i){
        printf("%d ", *get_ptr(v1, i, int));
    }   printf("\n");
    for(int i=0; i<size_of_cvector(v2); ++i){
        printf("%d ", *get_ptr(v2, i, int));
    }   printf("\n");

    exit(0);

    // cstring* str = CString(5);

    // concat(str, (const char*)"Hello C-Library!\n", 0);
    // concat(str, (const char*)"\tOk...\n", 0);

    // cstring* str2 = CString(1);

    // concat(str2, (const char*)"Hello ", 0);

    // printf("%s\n--------------\n%s\n", get_strptr(str), get_strptr(str2));
    // printf("comparison: %d\n", compare(str, str2, 0));
    // printf("comparison: %d\n", compare(str2, str, 0));
    // printf("comparison: %d\n", compare(str, str2, 6));
    // printf("comparison: %d\n", compare(str, str2, 7));

    // printf("%u\n", str->_str->_size);
    // printf("%u\n", str2->_str->_size);

    // copy_cstring(str2, str);

    // printf("%s\n--------------\n%s\n", get_strptr(str), get_strptr(str2));    
    // printf("%u\n", str->_str->_size);
    // printf("%u\n", str2->_str->_size);

    // ((char*)(str->_str->_data))[0] = 'a';
    // printf("%s\n--------------\n%s\n", get_strptr(str), get_strptr(str2)); 

    return 0;
}