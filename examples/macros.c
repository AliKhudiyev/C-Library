#include "cpplib.h"
#include <stdio.h>

int main(){

    // 1. Constructor (stack)
    MCV_init(vec, int, 1);

    // 2. Pushing 0, 1, 2, 3, 4
    for(int i=0; i<5; ++i){
        CV_push_back(&vec, &i);
    }

    // For Each macro
    int* iterator;
    MCV_For_Each(&vec, iterator, 
        printf("%d\n", *iterator);
    );

    // Enumerate macro
    size_t i;
    MCV_Enumerate(&vec, i, iterator, 
        printf("Iteration %zu: %d\n", i, *iterator);
    );

    // 3. Destructor
    CV_destruct(&vec);

    return 0;
}