#include <stdio.h>

#include "cpplib.h"

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

typedef struct{
    int ID;
    cstring name;
}Person;

void Person_destruct(void* ptr){
    CS_destruct(&((Person*)ptr)->name);
}

const char* Person_printer(void* data){
    Person* person = (Person*)data;
    char buffer[100];
    
    sprintf(buffer, "%d: %s", person->ID, CS_c_str(&person->name));
    CPrinter_set_buffer(buffer, 100);
    
    return CPrinter_get_buffer();
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
    
    // - - - - - - - - - - - - - - - - - - -

    // ctuple tuple;
    // CT_init(&tuple);

    // cstring* str = CString(10);
    // CS_append(str, "Hello\tWorld!\n", -1);

    // cstring str2;
    // CS_init(&str2, 3);
    // CS_append(&str2, "I am OK!\n", -1);

    // MCT_force_add(&tuple, int, 5);
    // MCT_force_add(&tuple, char, 'A');
    // MCT_force_add(&tuple, float, -3.1415);
    // CT_add(&tuple, &str, sizeof(cstring*));
    // CT_add(&tuple, &str2, sizeof(cstring));

    // CS_destruct(str);
    // CS_destruct(&str2);
    // free(str);

    // size_t i;
    // void* it;
    // printf("0: %d\n1: %c\n2: %f\n3: %s\n4: %s\n", 
    //         *MCT_front(&tuple, int), 
    //         *MCT_at(&tuple, 1, char),
    //         *MCT_at(&tuple, 2, float),
    //         CS_c_str(*MCT_at(&tuple, 3, cstring*)),
    //         CS_c_str(MCT_back(&tuple, cstring)));

    // CT_set_destructor(&tuple, 3, my_destruct);
    // CT_set_destructor(&tuple, 4, my_destruct2);

    // CT_destruct(&tuple);
    // CS_destruct(str);
    // CS_destruct(&str2);
    // free(str);

    // - - - - - - - - - - - - - - - - - - -
    
    return 0;
}