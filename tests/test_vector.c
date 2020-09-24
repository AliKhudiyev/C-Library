#include </usr/local/include/CUnit/CUnit.h>
#include </usr/local/include/CUnit/Basic.h>

#include <stdio.h>

#include "cvector.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

cvector *vec1, *vec2;
cvector *v1, *v2;

int my_sorter(Struct s1, Struct s2){
    return s1.weight >= s2.weight;
}

int compare_doubles(const void* a, const void* b){
    // return *(double*)a >= *(double*)b;
    return *(double*)a - *(double*)b;
}

int init_suite1(void){
    vec1 = CVector(sizeof(double), 0);
    vec2 = CVector(sizeof(double*), 5);

    v1 = CVector(sizeof(Struct*), 1);
    v2 = CVector(sizeof(Struct), 5);

    return 0;
}

int clean_suite1(void){
    CV_delete(vec1);
    CV_delete(vec2);

    CV_delete(v1);
    CV_delete(v2);
    
    return 0;
}

void test_constructor_destructor(){
    cvector* vec = CVector(sizeof(float*), 0);
    void* ptr = vec->_data;

    CU_ASSERT_PTR_NOT_NULL(vec);
    CU_ASSERT_PTR_NOT_NULL(ptr);

    CU_ASSERT_EQUAL(vec->_size, 0);
    CU_ASSERT_EQUAL(vec->_capacity, 1);
    CU_ASSERT_EQUAL(vec->_block_size, sizeof(float*));

    CV_delete(vec);
    
    CU_ASSERT_EQUAL(vec->_size, 0);
    CU_ASSERT_EQUAL(vec->_capacity, 0);
    CU_ASSERT_EQUAL(vec->_block_size, 0);
}

void test_push(){
    double val1 = -3.8;
    CV_push_back(vec1, &val1);

    CU_ASSERT_EQUAL(vec1->_size, 1);
    CU_ASSERT_EQUAL(vec1->_capacity, 1);
    CU_ASSERT_EQUAL(vec1->_block_size, sizeof(double));

    for(unsigned i=0; i<CV_size_of(vec1); ++i){
        double tmp = *MCV_get_ptr(vec1, i, double);
        CU_ASSERT_DOUBLE_EQUAL(tmp, -3.8, epsilon);
    }

    MCV_force_push_back(vec1, 1.4, double);

    CU_ASSERT_EQUAL(vec1->_size, 2);
    CU_ASSERT_EQUAL(vec1->_capacity, 2);
    CU_ASSERT_EQUAL(vec1->_block_size, sizeof(double));

    for(unsigned i=0; i<CV_size_of(vec1); ++i){
        double tmp = *MCV_get_ptr(vec1, i, double);
        CU_ASSERT_DOUBLE_EQUAL(tmp, !i? -3.8 : 1.4, epsilon);
    }

    unsigned capacity = 1;
    for(unsigned i=0; i<10; ++i){
        Struct* s = malloc(sizeof(Struct));
        s->weight = i/10.0;
        MCV_push_back(v1, &s, Struct*);

        Struct** tmp = MCV_get_ptr(v1, i, Struct*);

        if(i+1 > capacity) capacity *= 2;

        CU_ASSERT_DOUBLE_EQUAL(s->weight, (**tmp).weight, epsilon);
        CU_ASSERT_PTR_EQUAL(s, *tmp);

        CU_ASSERT_EQUAL(i+1, CV_size_of(v1));
        CU_ASSERT_EQUAL(v1->_capacity, capacity);
        CU_ASSERT_EQUAL(v1->_block_size, sizeof(Struct*));
    }
}

void test_erase(){
    ;
    CU_ASSERT(1);
}

void test_enlarge(){
    CU_ASSERT(1);
}

void test_insert(){
    CU_ASSERT(1);
}

void test_swap(){
    CU_ASSERT(1);
}

void test_check(){
    cvector* vec = CVector(sizeof(Struct*), 3);
    Struct* s[15];

    for(int i=0; i<15; ++i){
        s[i] = malloc(sizeof(Struct));
        MCV_push_back(vec, &s, Struct*);
    }

    int result;
    MCV_check(vec, s+2, result);
    CU_ASSERT(result);
    
    CV_delete(vec);
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
        (NULL == CU_add_test(pSuite, "test of push_back()", test_push)) ||
        (NULL == CU_add_test(pSuite, "test of erase()", test_erase)) ||
        (NULL == CU_add_test(pSuite, "test of enlarge()", test_enlarge)) ||
        (NULL == CU_add_test(pSuite, "test of insert()", test_insert)) ||
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        (NULL == CU_add_test(pSuite, "test of check()", test_check)) ||
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