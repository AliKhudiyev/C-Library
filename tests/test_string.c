#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "cstring.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

cstring *str1, *str2;

int my_sorter(Struct s1, Struct s2){
    return s1.weight >= s2.weight;
}

int compare_doubles(const void* a, const void* b){
    // return *(double*)a >= *(double*)b;
    return *(double*)a - *(double*)b;
}

int init_suite1(void){
    ;

    return 0;
}

int clean_suite1(void){
    CS_delete(str1);
    CS_delete(str2);
    
    return 0;
}

void test_constructor_destructor(){
    ;
}

void test_erase(){
    ;
    CU_ASSERT(1);
}

void test_insert(){
    CU_ASSERT(1);
}

void test_swap(){
    CU_ASSERT(1);
}

void test_sort(){
    cvector* vec = CVector(sizeof(Struct), 50);
    Struct s[50];
    double weights[50];

    for(int i=0; i<50; ++i){
        s[i].weight = weights[i] = rand()%100;
        MCV_push_back(vec, s+i, Struct);
    }

    MCV_sort(vec, my_sorter, Struct);
    qsort(weights, 50, sizeof(double), compare_doubles);

    for(int i=0; i<50; ++i){
        CU_ASSERT_DOUBLE_EQUAL(MCV_get_ptr(vec, i, Struct)->weight, weights[i], epsilon);
    }
    
    CV_delete(vec);
}

int main(){
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||
        (NULL == CU_add_test(pSuite, "test of erase()", test_erase)) ||
        (NULL == CU_add_test(pSuite, "test of insert()", test_insert)) ||
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        (NULL == CU_add_test(pSuite, "test of sort()", test_sort)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}