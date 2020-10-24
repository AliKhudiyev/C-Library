#include "cpplib.h"
#include <stdio.h>

int main(){
//  Stack-allocated vector
    cstring str;

    // 1. Constructor (stack)
    CS_init(&str, 1);

    /* 2. Operations = = = = = = = = = = = = = = */
    CS_append(&str, "Hello! ", -1);
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CS_push_back(&str, 'A'+i);
    }
    CS_erase(&str, 5);
    CS_replace(&str, 5, 1, "..., ");
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CS_destruct(&str);


//  Heap-allocated vector
    cstring* str_ptr;
    
    // 1. Constructor (heap)
    str_ptr = CString(1);

    /* 2. Operations = = = = = = = = = = = = = = */
    CS_append(str_ptr, "Hello! ", -1);
    for(int i=0; i<5; ++i){
        // Pushing values (value address needed)
        CS_push_back(str_ptr, 'A'+i);
    }
    CS_erase(str_ptr, 5);
    CS_replace(str_ptr, 5, 1, "..., ");
    /* = = = = = = = = = = = = = = = = = = = = = */

    // 3. Destructor
    CS_destruct(str_ptr);

    // 3. Free the allocated pointer manually as usual
    free(str_ptr);

    return 0;
}