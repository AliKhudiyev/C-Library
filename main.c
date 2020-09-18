#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int age;
}Person;

int main(){

    vector* vec = Vector(sizeof(Person), 5);

    for(int i=0; i<30; ++i){
        Person* p = malloc(sizeof(Person));
        p->age = i+1;
        push_back(vec, p, Person);
        // printf("age: %d\n", p->age);
        printf("size: %u, capacity: %u, block size: %u, added %d\n", vec->_size, vec->_capacity, vec->_block_size, (*get_ptr(vec, i, Person)).age);
    }

    printf("\nBEFORE ===============\n");
    for(unsigned i=0; i<vec->_size; ++i){
        if(!get_ptr(vec, i, Person)){
            printf("problem!\n");
            exit(1);
        }
        printf("%u, age: %d\n", i, (*get_ptr(vec, i, Person)).age);
    }

    printf("\nAFTER ===============\n");
    Person* p = malloc(sizeof(Person));
    p->age = -1;
    erase(vec, 2, Person);
    insert(vec, 2, p, Person);
    insert(vec, 29, p, Person);
    for(unsigned i=0; i<vec->_size; ++i){
        printf("%u, age: %d\n", i, (*get_ptr(vec, i, Person)).age);
    }

    delete_vector(vec);

    return 0;
}