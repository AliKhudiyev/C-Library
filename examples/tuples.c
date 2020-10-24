#include "cpplib.h"
#include <stdio.h>

int main(){
//  Stack-allocated vector
    ctuple tuple;

    // 1. Constructor (stack)
    CT_init(&tuple);

    /* 2. Operations = = = = = = = = = = = = = = */
    int key = 0;
    CT_add(&tuple, &key, sizeof(int));
    MCT_force_add(&tuple, char, 'A');
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CT_destruct(&tuple);


//  Heap-allocated vector
    ctuple* tuple_ptr;
    
    // 1. Constructor (heap)
    tuple_ptr = CTuple();

    /* 2. Operations = = = = = = = = = = = = = = */
    CT_add(&tuple, &key, sizeof(int));
    MCT_force_add(&tuple, char, 'A');
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CT_destruct(tuple_ptr);

    // 3. Free the allocated pointer manually as usual
    free(tuple_ptr);

    return 0;
}