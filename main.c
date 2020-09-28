#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int* age;
}Person;

bool_t my_sorter(int a, int b){
    return a >= b;
}

typedef struct{
    size_t _nrow, _ncol;
    cvector* _lines;
}CSV;

CSV* read_csv(const char* filepath){
    CSV* csv = malloc(sizeof(CSV));

    const char* cells[5][2] = {
        {"Hello There", "What's up?"},
        {"Are you good?", "Not at all!"},
        {"It is bad...", "Yeah"},
        {"Anyways, man.", "I gtg now."},
        {"Bye!", "Good bye."}
    };

    csv->_lines = CVector(sizeof(cvector), 1);
    for(unsigned i=0; i<5; ++i){
        cvector* vec = CVector(sizeof(cstring), 1);
        for(unsigned j=0; j<2; ++j){
            cstring* str = CString(1);
            printf("%s, ", cells[i][j]);
            CS_append(str, cells[i][j], -1);
            CV_push_back(vec, str);
            free(str);
        }   printf("\n");
        CV_push_back(csv->_lines, vec);
        free(vec);
    }
    
    return csv;
}

void csv_delete(CSV* csv){
    for(size_t i=0; i<CV_size(csv->_lines); ++i){
        for(size_t j=0; j<CV_size(MCV_at(csv->_lines, i, cvector)); ++j){
            CS_delete(MCV_at(MCV_at(csv->_lines, i, cvector), j, cstring));
        }
        CV_delete(MCV_at(csv->_lines, i, cvector));
    }
    CV_delete(csv->_lines);
    free(csv->_lines);
    free(csv);
}

void func(void* ptr){
    printf("=== Empty Destructor ===\n");
}

// for Person struct
void copy(void* dest, const void* src, size_t n_byte){
    if(!dest || !src) return ;

    for(int i=0; i<n_byte/sizeof(Person); ++i){
        Person person;
        person.age = malloc(4);
        *(person.age) = *(((Person*)src+i)->age);
        memcpy((Person*)dest+i, &person, sizeof(Person));
    }
}

// for Person struct
void delete(void* person){
    free(((Person*)person)->age);
}

int main(){

    // CSV* csv = read_csv("hey.txt");

    // printf("\n\nStatus: %lu (%lu), %lu (%lu)\n", CV_size(csv->_lines), CV_block_size(csv->_lines), CV_size(MCV_front(csv->_lines, cvector)), CV_block_size(MCV_front(csv->_lines, cvector)));
    // printf("Printing...\n\n");

    // for(unsigned i=0; i<5; ++i){
    //     for(unsigned j=0; j<2; ++j){
    //         printf("%s, ", CS_get_strptr(MCV_at(MCV_at(csv->_lines, i, cvector), j, cstring)));
    //     }   printf("\n");
    // }

    // csv_delete(csv);

    cvector v1, v2;
    // Person persons[6];

    printf("sizeof Person: %zu\n", sizeof(Person));

    CV_init(&v1, sizeof(Person), 2);
    CV_init(&v2, sizeof(Person), 4);
    
    for(int i=0; i<2; ++i){
        Person person;
        person.age = malloc(4);
        *person.age = i;
        CV_push_back(&v1, &person);
    }
    for(int i=2; i<6; ++i){
        Person person;
        person.age = malloc(4);
        *person.age = i;
        CV_push_back(&v2, &person);
    }

    // CV_push_back(&v1, &persons[0]);
    // CV_push_back(&v1, &persons[1]);

    // CV_push_back(&v2, &persons[2]);
    // CV_push_back(&v2, &persons[3]);
    // CV_push_back(&v2, &persons[4]);
    // CV_push_back(&v2, &persons[5]);

    printf("=== Before ===\n");
    printf("v1: %zu, %zu, %zu\n", CV_size(&v1), CV_capacity(&v1), CV_block_size(&v1));
    for(int i=0; i<CV_size(&v1); ++i){
        printf("%d\n", *(MCV_at(&v1, i, Person)->age));
    }
    printf("v2: %zu, %zu, %zu\n", CV_size(&v2), CV_capacity(&v2), CV_block_size(&v2));
    for(int i=0; i<CV_size(&v2); ++i){
        printf("%d\n", *(MCV_at(&v2, i, Person)->age));
    }

    CV_set_destructor(&v1, delete);
    // CV_copy(&v1, &v2);
    CV_set_deep_copy(&v1, copy);
    CV_deep_copy(&v1, &v2);

    printf("=== After ===\n");
    printf("v1: %zu, %zu, %zu\n", CV_size(&v1), CV_capacity(&v1), CV_block_size(&v1));
    for(int i=0; i<CV_size(&v1); ++i){
        printf("%d\n", *(MCV_at(&v1, i, Person)->age));
        free(MCV_at(&v1, i, Person)->age);
        // *(MCV_at(&v1, i, Person)->age) += 10;
    }

    printf("v2: %zu, %zu, %zu\n", CV_size(&v2), CV_capacity(&v2), CV_block_size(&v2));
    for(int i=0; i<CV_size(&v2); ++i){
        printf("%d\n", *(MCV_at(&v2, i, Person)->age));
        free(MCV_at(&v2, i, Person)->age);
    }

    CV_delete(&v1);
    CV_delete(&v2);

    // for(int i=0; i<2; ++i){
    //     free(persons[i].age);
    // }

    return 0;
}