#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "ctuple.h"
#include "cstring.h"

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

// Modifiers
void test_swap(){
    ctuple tuple1, tuple2;

    CT_init(&tuple1);
    CT_init(&tuple2);

    MCT_force_add(&tuple1, char, 'A');
    MCT_force_add(&tuple1, int, 4);

    MCT_force_add(&tuple2, float, 0.5);
    MCT_force_add(&tuple2, char, 'a');
    MCT_force_add(&tuple2, int, -2);

    CT_swap(&tuple1, &tuple2);

    CU_ASSERT_EQUAL(CT_size(&tuple1), 3);
    CU_ASSERT_EQUAL(CT_size(&tuple2), 2);

    CU_ASSERT_DOUBLE_EQUAL(*MCT_at(&tuple1, 0, float), 0.5, epsilon);
    CU_ASSERT_EQUAL(*MCT_at(&tuple1, 1, char), 'a');
    CU_ASSERT_EQUAL(*MCT_at(&tuple1, 2, int), -2);

    CU_ASSERT_EQUAL(*MCT_at(&tuple2, 0, char), 'A');
    CU_ASSERT_EQUAL(*MCT_at(&tuple2, 1, int), 4);

    CT_destruct(&tuple1);
    CT_destruct(&tuple2);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void test_at(){
    ctuple tuple;
    CT_init(&tuple);

    // - - - - - - - - - - - - - - - -
    cstring str;
    CS_init(&str, 1);
    MCV_init(vec, double, 1);

    CS_assign(&str, "Hello, C-Library!", -1);
    MCV_force_push_back(&vec, 3.1415, double);
    MCV_force_push_back(&vec, -1, double);
    // - - - - - - - - - - - - - - - -

    MCT_force_add(&tuple, float, 0.5);
    MCT_force_add(&tuple, char, 'a');
    MCT_force_add(&tuple, int, -2);
    MCT_force_add(&tuple, char*, "Hello, World!");
    CT_add(&tuple, &str, sizeof(cstring));
    CT_add(&tuple, &vec, sizeof(cvector));

    CU_ASSERT_DOUBLE_EQUAL(*MCT_at(&tuple, 0, float), 0.5, epsilon);
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 1, char), 'a');
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 2, int), -2);
    CU_ASSERT(!strcmp(*MCT_at(&tuple, 3, char*), "Hello, World!"));
    CU_ASSERT(!strcmp(CS_c_str(MCT_at(&tuple, 4, cstring)), "Hello, C-Library!"));
    CU_ASSERT_DOUBLE_EQUAL(*MCV_front(MCT_at(&tuple, 5, cvector), double), 3.1415, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_back(MCT_at(&tuple, 5, cvector), double), -1, epsilon);

    CS_destruct(&str);
    CV_destruct(&vec);
    CT_destruct(&tuple);
}

void test_front(){
    ctuple tuple;
    CT_init(&tuple);

    CU_ASSERT_PTR_EQUAL(MCT_front(&tuple, int), NULL);

    MCT_force_add(&tuple, float, 0.5);
    CU_ASSERT_DOUBLE_EQUAL(*MCT_front(&tuple, float), 0.5, epsilon);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_DOUBLE_EQUAL(*MCT_front(&tuple, float), 0.5, epsilon);

    MCT_force_add(&tuple, int, -2);
    CU_ASSERT_DOUBLE_EQUAL(*MCT_front(&tuple, float), 0.5, epsilon);

    CT_destruct(&tuple);
}

void test_back(){
    ctuple tuple;
    CT_init(&tuple);

    CU_ASSERT_PTR_EQUAL(MCT_back(&tuple, float), NULL);

    MCT_force_add(&tuple, float, 0.5);
    CU_ASSERT_DOUBLE_EQUAL(*MCT_back(&tuple, float), 0.5, epsilon);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_EQUAL(*MCT_back(&tuple, char), 'a');

    MCT_force_add(&tuple, int, -2);
    CU_ASSERT_EQUAL(*MCT_back(&tuple, int), -2);

    CT_destruct(&tuple);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void test_add(){
    ctuple tuple;
    CT_init(&tuple);

    CU_ASSERT_EQUAL(CT_size(&tuple), 0);
    CU_ASSERT_PTR_EQUAL(MCT_front(&tuple, void), NULL);
    CU_ASSERT_PTR_EQUAL(MCT_at(&tuple, 1, void), NULL);
    CU_ASSERT_PTR_EQUAL(MCT_back(&tuple, void), NULL);

    MCT_force_add(&tuple, float, 0.5);
    CU_ASSERT_EQUAL(CT_size(&tuple), 1);
    CU_ASSERT_DOUBLE_EQUAL(*MCT_front(&tuple, float), 0.5, epsilon);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_EQUAL(CT_size(&tuple), 2);
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 1, char), 'a');

    MCT_force_add(&tuple, int, -2);
    CU_ASSERT_EQUAL(CT_size(&tuple), 3);
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 2, int), -2);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_EQUAL(CT_size(&tuple), 4);
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 3, char), 'a');

    MCT_force_add(&tuple, int, -3);
    CU_ASSERT_EQUAL(CT_size(&tuple), 5);
    CU_ASSERT_EQUAL(*MCT_at(&tuple, 4, int), -3);

    CT_destruct(&tuple);
}

void test_find(){
    ctuple tuple;
    CT_init(&tuple);

    size_t result;

    MCT_force_find(result, &tuple, float, 0.5);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    MCT_force_add(&tuple, float, 0.5);
    MCT_force_find(result, &tuple, float, 0.5);
    CU_ASSERT_EQUAL(result, 0);
    MCT_force_find(result, &tuple, char, 'a');
    CU_ASSERT_EQUAL(result, (size_t)-1);

    MCT_force_add(&tuple, char, 'a');
    MCT_force_find(result, &tuple, float, 0.5);
    CU_ASSERT_EQUAL(result, 0);
    MCT_force_find(result, &tuple, char, 'a');
    CU_ASSERT_EQUAL(result, 1);

    MCT_force_add(&tuple, int, -2);
    MCT_force_find(result, &tuple, float, 0.5);
    CU_ASSERT_EQUAL(result, 0);
    MCT_force_find(result, &tuple, char, 'a');
    CU_ASSERT_EQUAL(result, 1);
    MCT_force_find(result, &tuple, int, -2);
    CU_ASSERT_EQUAL(result, 2);

    MCT_force_add(&tuple, char, 'a');
    MCT_force_find(result, &tuple, float, 0.5);
    CU_ASSERT_EQUAL(result, 0);
    MCT_force_find(result, &tuple, char, 'a');
    CU_ASSERT_EQUAL(result, 1);
    MCT_force_find(result, &tuple, int, -2);
    CU_ASSERT_EQUAL(result, 2);
    MCT_force_find(result, &tuple, float, 0.f);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    CT_destruct(&tuple);
}

void test_size(){
    ctuple tuple;
    CT_init(&tuple);

    CU_ASSERT_EQUAL(CT_size(&tuple), 0);

    MCT_force_add(&tuple, float, 0.5);
    CU_ASSERT_EQUAL(CT_size(&tuple), 1);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_EQUAL(CT_size(&tuple), 2);

    MCT_force_add(&tuple, int, -2);
    CU_ASSERT_EQUAL(CT_size(&tuple), 3);

    MCT_force_add(&tuple, char, 'a');
    CU_ASSERT_EQUAL(CT_size(&tuple), 4);

    MCT_force_add(&tuple, int, -3);
    CU_ASSERT_EQUAL(CT_size(&tuple), 5);

    CT_destruct(&tuple);
}
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
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||
        
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        
        (NULL == CU_add_test(pSuite, "test of at()", test_at)) ||
        (NULL == CU_add_test(pSuite, "test of front()", test_front)) ||
        (NULL == CU_add_test(pSuite, "test of back()", test_back)) ||
        
        (NULL == CU_add_test(pSuite, "test of add", test_add)) ||
        (NULL == CU_add_test(pSuite, "test of find", test_find)) ||
        (NULL == CU_add_test(pSuite, "test of size", test_size)))
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