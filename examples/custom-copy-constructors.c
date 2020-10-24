#include "cpplib.h"
#include <stdio.h>

// Custom copy constructor for int pointer
// Remember that ptr points to to the int pointer(not to int directly)
void copy_int_ptr(void* dest, const void* src, size_t size){
    for(size_t i=0; i<size/sizeof(int*); ++i){
        int* tmp = (int*)malloc(sizeof(int));
        *tmp = *(((int**)src)[i]);
        ((int**)dest)[i] = tmp;
    }
}

// Custom destructor for int pointer
// Remember that ptr points to to the int pointer(not to int directly)
void free_int_ptr(void* ptr){
    free(*(int**)ptr);
}

int main(){

    // 1. Constructor (stack)
    MCV_init(vec, int*, 1);

    // 2. Setting the custom copy constructor & destructor
    CV_set_deep_copy(&vec, copy_int_ptr);   // Not necessary since vec is the destination
    CV_set_destructor(&vec, free_int_ptr);

    /* 3. Creating and storing a pointer in the vector */
    int* a = (int*)malloc(sizeof(int));
    *a = 1;

    CV_push_back(&vec, &a);
    /* = = = = = = = = = = = = = = = = = = = = = = = = */

    /* 4. Deep copy by copy constructor  = = = = = = = */
    MCV_init(vec_copy, int*, 1);
    CV_set_deep_copy(&vec_copy, copy_int_ptr);
    CV_set_destructor(&vec_copy, free_int_ptr);

    CV_deep_copy(&vec_copy, &vec);
    /* = = = = = = = = = = = = = = = = = = = = = = = = */

    // 5. Destructor
    CV_destruct(&vec);
    CV_destruct(&vec_copy);

    // No custom destructor is set!
    // Need a manual free of the allocated int!
    free(a);

    return 0;
}