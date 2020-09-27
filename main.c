#include <stdio.h>

#include "cpplib.h"

typedef struct{
    int age;
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
    CV_set_destructor(csv->_lines, CV_delete);
    for(unsigned i=0; i<5; ++i){
        cvector* vec = CVector(sizeof(cstring), 1);
        CV_set_destructor(vec, CS_delete);
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

void func(void* ptr){
    printf("=== Empty Destructor ===\n");
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

    // CV_delete(csv->_lines);
    // free(csv->_lines);
    // free(csv);

    cvector* v1 = CVector(sizeof(cvector), 1);
    cvector* v2 = CVector(sizeof(cvector), 1);
    cvector* v3 = CVector(sizeof(int), 1);

    CV_set_destructor(v1, CV_delete);
    CV_set_destructor(v2, CV_delete);
    CV_set_destructor(v3, NULL);

    MCV_force_push_back(v3, 5, int);
    CV_push_back(v1, v3);
    CV_push_back(v2, v3);

    // CV_delete(v3);
    free(v3);
    printf("%d, %d\n", 
        *MCV_front(MCV_front(v1, cvector), int), 
        *MCV_front(MCV_front(v2, cvector), int));

    CV_delete(v1);
    free(v1);
    
    for(size_t i=0; i<CV_size(v2); ++i){
        CV_delete(CV_at(v2, i));
    }

    CV_delete(v2);
    free(v2);

    return 0;
}