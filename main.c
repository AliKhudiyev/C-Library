#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int age;
}Person;

bool_t my_sorter(int a, int b){
    return a >= b;
}

int main(){

    cpair* pair = CPair(1, 4);

    cvector* vec = CVector(4, 2);

    // MCV_force_push_back(vec, 2, int);
    MCV_force_push_back(vec, -1, int);
    int i = 2;
    CV_push_back(vec, &i);

    force_make_pair(pair, 'a', vec, char);

    printf("key: %s\n", get_firstptr(pair, char));
    printf(" > %d\n", *get_secondptr(pair, 0, int));
    printf(" > %d\n", *get_secondptr(pair, 1, int));

    if(!get_secondptr(pair, 2, int)){
        printf("null\n");
    }

    delete_pair(pair);
    
    return 0;
}