#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int* age;
}Person;

typedef struct{
    int id;
}Struct;

bool_t my_sorter(int a, int b){
    return a >= b;
}

typedef struct{
    cstring _context;
}File;

typedef struct{
    size_t _nrow, _ncol;
    cvector* _context;
}CSV;

File* read_file(const char* filepath){
    File* file = (File*)malloc(sizeof(File));
    CS_init(&file->_context, 0);

    FILE* in = fopen(filepath, "r");
    char c;
    while((c=fgetc(in)) != EOF){
        CS_push_back(&file->_context, c);
    }   CS_push_back(&file->_context, 0);
    fclose(in);

    return file;
}

CSV* read_csv(const char* filepath){
    CSV* csv = malloc(sizeof(CSV));

    const char* cells[5][2] = {
        {"Hello There", "What's up?"},
        {"Are you good?", "Not at all!"},
        {"It is bad...", "Yeah"},
        {"Anyways, man.", "I gtg now."},
        {"Bye!", "Good bye."}
    };

    csv->_context = CVector(sizeof(cvector), 1);
    for(unsigned i=0; i<5; ++i){
        cvector vec;
        CV_init(&vec, sizeof(cstring), 1);

        for(unsigned j=0; j<2; ++j){
            cstring str;
            CS_init(&str, 1);

            printf("%s, ", cells[i][j]);
            CS_append(&str, cells[i][j], -1);
            CV_push_back(&vec, &str);
        }   printf("\n");
        CV_push_back(csv->_context, &vec);
    }
    
    return csv;
}

void csv_delete(CSV* csv){
    for(size_t i=0; i<CV_size(csv->_context); ++i){
        for(size_t j=0; j<CV_size(MCV_at(csv->_context, i, cvector)); ++j){
            CS_delete(MCV_at(MCV_at(csv->_context, i, cvector), j, cstring));
        }
        CV_delete(MCV_at(csv->_context, i, cvector));
    }
    CV_delete(csv->_context);
    free(csv->_context);
    csv->_context = NULL;
}

void delete_file(File* file){
    CS_delete(&file->_context);
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

    // printf("\n\nStatus: %lu (%lu), %lu (%lu)\n", 
    //     CV_size(csv->_context), 
    //     CV_block_size(csv->_context), 
    //     CV_size(MCV_front(csv->_context, cvector)), 
    //     CV_block_size(MCV_front(csv->_context, cvector)));
    // printf("Printing...\n\n");

    // for(unsigned i=0; i<5; ++i){
    //     for(unsigned j=0; j<2; ++j){
    //         printf("%s, ", CS_c_str(MCV_at(MCV_at(csv->_context, i, cvector), j, cstring)));
    //     }   printf("\n");
    // }

    // csv_delete(csv);
    // free(csv);

    // File* file = read_file("../example.txt");
    // printf("= = = = = = = = = = =\n%s\n= = = = = = = = = =\n", CS_c_str(&file->_context));
    // delete_file(file);
    // free(file);

    cset set;
    CSet_init(&set, sizeof(char), 1);

    for(size_t i=0; i<CSet_size(&set); ++i){
        printf("- %c ", *MCSet_at(&set, i, char));
    }   printf("\n");

    MCSet_emplace(&set, char, 'A');
    MCSet_emplace(&set, char, 'B');
    MCSet_emplace(&set, char, 'C');

    for(size_t i=0; i<CSet_size(&set); ++i){
        printf("- %c ", *MCSet_at(&set, i, char));
    }   printf("\n");

    MCSet_emplace(&set, char, 'B');
    MCSet_emplace(&set, char, 'A');
    MCSet_emplace(&set, char, 'D');
    MCSet_emplace(&set, char, 'Z');

    for(size_t i=0; i<CSet_size(&set); ++i){
        printf("- %c ", *MCSet_at(&set, i, char));
    }   printf("\n");

    CSet_delete(&set);

    return 0;
}