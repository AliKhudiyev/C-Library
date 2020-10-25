#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "ctuple.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

ctuple *t1, *t2;

int init_suite(void){

    t1 = CTuple();
    t2 = CTuple();

    return 0;
}

int clean_suite(void){

    CT_delete(t1);
    CT_delete(t2);

    free(t1);
    free(t2);
    
    return 0;
}

// Constructor and Destructor
void test_constructor_destructor(){
    ctuple* tuple = CTuple(0);

    // CU_ASSERT_EQUAL(CT_size(tuple), 0);
    // CU_ASSERT_EQUAL(CT_capacity(tuple), 1);

    CT_delete(tuple);
    free(tuple);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// TO DO

// Additional
// = = = = = = = = = = = = = = = = = = = = = = =

int main(){
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Tuple Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||
        0
        )
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