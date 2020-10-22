#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int* age;
    char name[30];
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

cstring* file_readline(const File* file, size_t index){
    size_t beg = 0, end = CS_find(&file->_context, "\n", 0);
    
    for(size_t i=0; i<index; ++i){
        beg = end + 1;
        end = CS_find(&file->_context, "\n", beg);
        if(end == -1) return NULL;
        end += beg;
    }

    return CS_substr(&file->_context, beg, end-beg);
}

size_t CS_read_token(cstring* token, const cstring* string, const char* delimeter, size_t position){
    size_t end = CS_find(string, delimeter, position);
    CS_clear(token);
    if(end == -1){
        CS_append(token, CS_c_str(string)+position, CS_size(string)-position);
        return -1;
    }
    if(CS_back(string) == '\n') end -= 1;
    CS_append(token, CS_c_str(string)+position, end);
    return end+position+1;
}

void delete_file(File* file){
    CS_delete(&file->_context);
}

CSV* read_csv(const char* filepath){
    File* file = read_file(filepath);
    CSV* csv = malloc(sizeof(CSV));

    csv->_nrow = csv->_ncol = 0;
    csv->_context = CVector(sizeof(cvector), 1);
    cstring* line;
    size_t r = 0;

    while((line=file_readline(file, r++))){
        printf("line: %s\n", CS_c_str(line));

        cvector vec;
        CV_init(&vec, sizeof(cstring), 1);
        size_t position = 0, ncol = 0;

        do{
            ++ncol;
            if(!csv->_nrow) ++csv->_ncol;
            cstring token;
            CS_init(&token, 1);
            position=CS_read_token(&token, line, ",", position);
            printf("%s|", CS_c_str(&token));
            CV_push_back(&vec, &token);
        }while(position != -1);
        printf("\n");

        if(ncol == csv->_ncol){
            ++csv->_nrow;
            CV_push_back(csv->_context, &vec);
            // csv->_ncol = ncol;
        }
        CS_delete(line);
        free(line);
    }

    delete_file(file);
    free(file);
    
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

void my_free(void* ptr){
    free(*((int**)ptr));
}

void my_copy(void* dest, const void* src, size_t n_byte){
    for(size_t i=0; i<n_byte/sizeof(int*); ++i){
        int* ptr = malloc(4);
        memcpy(ptr, *((int**)src+i), 4);
        memcpy(dest+i*sizeof(int*), &ptr, sizeof(int*));
    }
}

typedef struct{
    int a, *b;
}My_Class;

void MyClass_destruct(void* ptr){
    free(((My_Class*)ptr)->b);
}

void MyClass_copy(void* dest, const void* src, size_t n_byte){
    for(size_t i=0; i<n_byte/sizeof(My_Class); ++i){
        memcpy(&((My_Class*)dest)[i].a, &((My_Class*)src)[i].a, sizeof(int));
    
        int* ptr = malloc(sizeof(int));
        memcpy(ptr, ((My_Class*)src)[i].b, sizeof(int));
        memcpy(&((My_Class*)dest)[i].b, &ptr, sizeof(int*));
    }
}

int main(){

    // CSV* csv = read_csv("../hey.txt");

    // printf("\n\nStatus: %lu (%lu), %lu (%lu)\n", 
    //     CV_size(csv->_context), 
    //     CV_block_size(csv->_context), 
    //     CV_size(MCV_front(csv->_context, cvector)), 
    //     CV_block_size(MCV_front(csv->_context, cvector)));
    // printf("Printing...[%zu x %zu]\n\n", csv->_nrow, csv->_ncol);

    // for(unsigned i=0; i<csv->_nrow; ++i){
    //     // printf("> %u\n", i);
    //     for(unsigned j=0; j<csv->_ncol; ++j){
    //         // printf("  > %u\n", j);
    //         // CS_c_str(MCV_at(MCV_at(csv->_context, i, cvector), j, cstring));
    //         printf("%s, ", CS_c_str(MCV_at(MCV_at(csv->_context, i, cvector), j, cstring)));
    //     }   printf("\n");
    // }

    // csv_delete(csv);
    // free(csv);

    cvector vec1, vec2;

    CV_init(&vec1, sizeof(My_Class), 1);
    CV_init(&vec2, sizeof(My_Class), 1);

    CV_set_deep_copy(&vec1, MyClass_copy);
    CV_set_deep_copy(&vec2, MyClass_copy);

    CV_set_destructor(&vec1, MyClass_destruct);
    CV_set_destructor(&vec2, MyClass_destruct);

    My_Class obj1, obj2;

    obj1.a = 0;
    obj1.b = malloc(4); *obj1.b = 1;

    obj2.a = 2;
    obj2.b = malloc(4); *obj2.b = 3;

    CV_push_back(&vec1, &obj1);
    CV_push_back(&vec2, &obj2);

    printf("%d, %d - %d, %d\n",
            MCV_front(&vec1, My_Class)->a, *(MCV_front(&vec1, My_Class)->b),
            MCV_front(&vec2, My_Class)->a, *(MCV_front(&vec2, My_Class)->b));

    CV_deep_copy(&vec1, &vec2);

    printf("%d, %d - %d, %d\n",
            MCV_front(&vec1, My_Class)->a, *(MCV_front(&vec1, My_Class)->b),
            MCV_front(&vec2, My_Class)->a, *(MCV_front(&vec2, My_Class)->b));

    CV_destruct(&vec1);
    CV_destruct(&vec2);

    return 0;
}