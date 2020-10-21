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
    CV_destruct(*((cvector**)ptr));
    free(*((cvector**)ptr));
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

    cvector vec;
    cvector str1, str2;
    CV_init(&vec, sizeof(cstring), 1);
    CV_init(&str1, 4, 1);
    CV_init(&str2, 1, 1);

    // MCV_force_push_back(&vec, 7, int);
    // MCV_force_push_back(&vec, -3, int);
    // MCV_force_push_back(&vec, 2, int);

    MCV_force_push_back(&str1, 5, int);
    MCV_force_push_back(&str1, 3, int);
    MCV_force_push_back(&str1, -2, int);

    MCV_force_push_back(&str2, 'A', char);
    MCV_force_push_back(&str2, 'l', char);
    MCV_force_push_back(&str2, 'i', char);

    CV_push_back(&vec, &str1);
    CV_push_back(&vec, &str2);

    // int* it;
    // MCV_For_Each(&vec, it, 
    //     printf("%d\n", *it);
    // );

    cvector* it;
    size_t i;
    int sum = 0;
    MCV_Enumerate(&vec, i, it, 
        printf("Iteration # %zu\n", i);
        size_t j;
        if(CV_block_size(it) == 4){
            int* num;
            MCV_For_Each(it, num, 
                sum += *num;
            );
        }
        else if(i == 1){
            char* c;
            MCV_Enumerate(it, j, c, 
                printf("%zu: %c\n", j, *c);
            );
        }
        // printf("%zu: %d\n", i, *it);
        // sum += *it;
    );
    printf("The sum is %d.\n", sum);

    return 0;
}