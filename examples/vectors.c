#include "cpplib.h"
#include <stdio.h>

int main(){
//  Stack-allocated vector
    cvector vec;

    // 1. Constructor (stack)
    CV_init(&vec, sizeof(int), 1);

    /* 2. Operations = = = = = = = = = = = = = = */
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CV_push_back(&vec, &i);
    }
    // Pushing values (value type needed)
    MCV_force_push_back(&vec, 5, int);
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CV_destruct(&vec);


//  Heap-allocated vector
    cvector* vec_ptr;
    
    // 1. Constructor (heap)
    vec_ptr = CVector(sizeof(int), 1);

    /* 2. Operations = = = = = = = = = = = = = = */
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CV_push_back(&vec, &i);
    }
    // Pushing values (value type needed)
    MCV_force_push_back(&vec, 5, int);
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CV_destruct(vec_ptr);

    // 3. Free the allocated pointer manually as usual
    free(vec_ptr);

    return 0;
}