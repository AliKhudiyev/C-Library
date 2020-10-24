#include "cpplib.h"
#include <stdio.h>

// Custom destructor for int pointer
// Remember that ptr points to to the int pointer(not to int directly)
void free_int_ptr(void* ptr){
    free(*(int**)ptr);
}

int main(){

    // 1. Constructor (stack)
    MCV_init(vec, int*, 1);

    // 2. Setting the custom destructor
    CV_set_destructor(&vec, free_int_ptr);

    /* 3. Creating and storing a pointer in the vector */
    int* a = (int*)malloc(sizeof(int));
    *a = 1;

    CV_push_back(&vec, &a);
    /* = = = = = = = = = = = = = = = = = = = = = = = = */

    // 4. Destructor
    CV_destruct(&vec);

    return 0;
}