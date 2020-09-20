#include </usr/local/include/CUnit/CUnit.h>
#include </usr/local/include/CUnit/Basic.h>

#include <stdio.h>

#include "cvector.h"

typedef struct{
    char name[30];
    double weight;
}Struct;

cvector *vec1, *vec2;
cvector *v1, *v2;

int init_suite1(void){
    vec1 = CVector(sizeof(double), 0);
    vec2 = CVector(sizeof(double), 0);

    v1 = CVector(sizeof(Struct), 1);
    v2 = CVector(sizeof(Struct), 5);

    return 0;
}

int clean_suite1(void){
    delete_cvector(vec1);
    delete_cvector(vec2);

    delete_cvector(v1);
    delete_cvector(v2);
    
    return 0;
}

void test_push(){
    ;
    CU_ASSERT(1);
}

void test_erase(){
    CU_ASSERT(1);
}

void test_enlarge(){
    ;
}

void test_insert(){
    ;
}

void test_swap(){
    ;
}

void test_exists(){
    ;
}

void test_sort(){
    ;
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
    if ((NULL == CU_add_test(pSuite, "test of fprintf()", test_push)) ||
        (NULL == CU_add_test(pSuite, "test of fread()", test_erase)))
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