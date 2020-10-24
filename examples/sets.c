#include "cpplib.h"
#include <stdio.h>

int main(){
//  Stack-allocated vector
    cset set;

    // 1. Constructor (stack)
    CSet_init(&set, sizeof(int), 1);

    /* 2. Operations = = = = = = = = = = = = = = */
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CSet_insert(&set, &i);
    }
    // Pushing values (value type needed)
    MCSet_emplace(&set, int, 2);
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CV_destruct(&set);


//  Heap-allocated vector
    cset* set_ptr;
    
    // 1. Constructor (heap)
    set_ptr = CSet(sizeof(int), 1);

    /* 2. Operations = = = = = = = = = = = = = = */
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CSet_insert(&set, &i);
    }
    // Pushing values (value type needed)
    MCSet_emplace(&set, int, 2);
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CSet_destruct(set_ptr);

    // 3. Free the allocated pointer manually as usual
    free(set_ptr);

    return 0;
}