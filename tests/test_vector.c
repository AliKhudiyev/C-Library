#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "cvector.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

cvector *v1, *v2;

int my_sorter(Struct s1, Struct s2){
    return s1.weight >= s2.weight;
}

int compare_doubles(const void* a, const void* b){
    // return *(double*)a >= *(double*)b;
    return *(double*)a - *(double*)b;
}

int init_suite1(void){

    v1 = CVector(sizeof(Struct*), 1);
    v2 = CVector(sizeof(Struct), 5);

    return 0;
}

int clean_suite1(void){

    CV_delete(v1);
    CV_delete(v2);

    free(v1);
    free(v2);
    
    return 0;
}

// Consturctor and Destructor
void test_constructor_destructor(){
    cvector* vec = CVector(sizeof(float*), 0);
    void* ptr = vec->_data;

    CU_ASSERT_PTR_NOT_NULL(vec);
    CU_ASSERT_PTR_NOT_NULL(ptr);

    CU_ASSERT_EQUAL(CV_size(vec), 0);
    CU_ASSERT_EQUAL(CV_capacity(vec), 1);
    CU_ASSERT_EQUAL(vec->_block_size, sizeof(float*));

    CV_delete(vec);
    
    CU_ASSERT_EQUAL(vec->_size, 0);
    CU_ASSERT_EQUAL(vec->_capacity, 0);
    CU_ASSERT_EQUAL(vec->_block_size, 0);

    free(vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
void test_size(){
    cvector* vec = CVector(sizeof(char), 1);

    for(size_t i=0; i<100; ++i){
        CU_ASSERT_EQUAL(CV_size(vec), i);
        MCV_force_push_back(vec, 'a', char);
    }

    for(size_t i=0; i<50; ++i){
        CU_ASSERT_EQUAL(CV_size(vec), 100-i);
        if(i%2) CV_pop_back(vec);
        else CV_erase(vec, i);
    }

    CV_delete(vec);
    free(vec);
}

void test_resize(){
    cvector* vec = CVector(sizeof(char), 2);

    CU_ASSERT_EQUAL(CV_capacity(vec), 2);

    CV_resize(vec, 1);
    CU_ASSERT_EQUAL(CV_capacity(vec), 2);

    CV_resize(vec, 3);
    CU_ASSERT_EQUAL(CV_capacity(vec), 3);

    CV_delete(vec);
    free(vec);
}

void test_capacity(){
    cvector* vec = CVector(sizeof(char), 0);

    size_t capacity = 1;
    for(size_t i=0; i<100; ++i){
        CU_ASSERT_EQUAL(CV_capacity(vec), capacity);
        MCV_force_push_back(vec, 'a', char);
        if(capacity <= i) capacity *= 2;
    }
    
    CV_delete(vec);
    free(vec);
}

void test_empty(){
    cvector* vec = CVector(sizeof(char), 2);

    CU_ASSERT(CV_empty(vec));
    MCV_force_push_back(vec, 'a', char);
    CU_ASSERT(!CV_empty(vec));
    MCV_force_push_back(vec, 'b', char);
    CV_pop_back(vec);
    CU_ASSERT(!CV_empty(vec));
    CV_pop_back(vec);
    CU_ASSERT(CV_empty(vec));

    CV_delete(vec);
    free(vec);
}

void test_shrink_to_fit(){
    cvector* vec = CVector(sizeof(char), 1);

    MCV_emplace_back(vec, char, 'a');
    MCV_emplace_back(vec, char, 'b');
    MCV_emplace_back(vec, char, 'c');

    CU_ASSERT_EQUAL(CV_capacity(vec), 4);
    CV_shrink_to_fit(vec);
    CU_ASSERT_EQUAL(CV_capacity(vec), 3);

    CV_delete(vec);
    free(vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void test_at(){
    cvector* vec = CVector(sizeof(int), 5);

    for(unsigned i=0; i<5; ++i){
        CU_ASSERT_PTR_EQUAL(CV_at(vec, i), NULL);
        CV_push_back(vec, &i);
        CU_ASSERT_PTR_EQUAL(CV_at(vec, i), vec->_data+i*vec->_block_size);
    }

    CV_delete(vec);
    free(vec);
}

void test_front(){
    cvector* vec = CVector(sizeof(int), 5);

    CU_ASSERT_PTR_EQUAL(CV_front(vec), NULL);
    MCV_force_push_back(vec, 0, int);
    CU_ASSERT_PTR_EQUAL(CV_front(vec), vec->_data);
    MCV_force_push_back(vec, 1, int);
    CU_ASSERT_PTR_EQUAL(CV_front(vec), vec->_data);

    CV_delete(vec);
    free(vec);
}

void test_back(){
    cvector* vec = CVector(sizeof(int), 5);

    CU_ASSERT_PTR_EQUAL(CV_back(vec), NULL);
    MCV_force_push_back(vec, 0, int);
    CU_ASSERT_PTR_EQUAL(CV_back(vec), vec->_data);
    MCV_force_push_back(vec, 1, int);
    CU_ASSERT_PTR_EQUAL(CV_back(vec), vec->_data+vec->_block_size);

    CV_delete(vec);
    free(vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void test_push_back(){
    cvector* vec = CVector(sizeof(char), 2);

    for(unsigned i=0; i<10; ++i){
        char tmp = 64+i;
        CU_ASSERT_EQUAL(CV_size(vec), i);
        CV_push_back(vec, (const void*)&tmp);
        CU_ASSERT_EQUAL(*MCV_back(vec, char), tmp);
    }

    CV_delete(vec);
    free(vec);
}

void test_pop_back(){
    cvector* vec = CVector(sizeof(char), 3);

    MCV_force_push_back(vec, 'a', char);
    CU_ASSERT_EQUAL('a', *MCV_back(vec, char));

    MCV_force_push_back(vec, 'b', char);
    CU_ASSERT_EQUAL('b', *MCV_back(vec, char));

    MCV_force_push_back(vec, 'c', char);
    CU_ASSERT_EQUAL('c', *MCV_back(vec, char));

    CU_ASSERT_EQUAL(3, CV_size(vec));

    CV_pop_back(vec);
    CU_ASSERT_EQUAL(2, CV_size(vec));
    CU_ASSERT_EQUAL('b', *MCV_back(vec, char));

    CV_pop_back(vec);
    CU_ASSERT_EQUAL(1, CV_size(vec));
    CU_ASSERT_EQUAL('a', *MCV_back(vec, char));

    CV_pop_back(vec);
    CU_ASSERT_EQUAL(0, CV_size(vec));
    CU_ASSERT_PTR_EQUAL(NULL, MCV_back(vec, char));

    CV_delete(vec);
    free(vec);
}

void test_insert(){
    cvector* vec = CVector(sizeof(double), 3);
    
    MCV_force_insert(vec, -1, 0.5, double);
    CU_ASSERT_EQUAL(CV_size(vec), 0);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 0, double), NULL);
    
    MCV_force_insert(vec, 1, 1, double);
    CU_ASSERT_EQUAL(CV_size(vec), 0);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 0, double), NULL);
    
    MCV_force_insert(vec, 3, 1.5, double);
    CU_ASSERT_EQUAL(CV_size(vec), 0);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 0, double), NULL);

    MCV_force_insert(vec, 0, 2, double);
    CU_ASSERT_EQUAL(CV_size(vec), 1);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 0, double), 2, epsilon);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 1, double), NULL);

    MCV_force_insert(vec, 0, 2.5, double);
    CU_ASSERT_EQUAL(CV_size(vec), 2);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 0, double), 2.5, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 1, double), 2, epsilon);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 2, double), NULL);

    MCV_force_insert(vec, 1, 3, double);
    CU_ASSERT_EQUAL(CV_size(vec), 3);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 0, double), 2.5, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 1, double), 3, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 2, double), 2, epsilon);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 3, double), NULL);

    MCV_force_insert(vec, 3, 3.5, double);
    CU_ASSERT_EQUAL(CV_size(vec), 4);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 0, double), 2.5, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 1, double), 3, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 2, double), 2, epsilon);
    CU_ASSERT_DOUBLE_EQUAL(*MCV_at(vec, 3, double), 3.5, epsilon);
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 4, double), NULL);

    CV_delete(vec);
    free(vec);
}

void test_erase(){
    cvector* vec = CVector(sizeof(char), 5);

    CV_erase(vec, -1);
    CV_erase(vec, 0);
    CV_erase(vec, 10);

    CU_ASSERT_EQUAL(CV_size(vec), 0);

    MCV_force_push_back(vec, 'a', char);
    MCV_force_push_back(vec, 'b', char);
    MCV_force_push_back(vec, 'c', char);
    MCV_force_push_back(vec, 'd', char);
    MCV_force_push_back(vec, 'e', char);

    CV_erase(vec, 0);
    CU_ASSERT_EQUAL(CV_size(vec), 4);
    CV_erase(vec, 1);
    CU_ASSERT_EQUAL(CV_size(vec), 3);
    CV_erase(vec, CV_size(vec)-1);
    CU_ASSERT_EQUAL(CV_size(vec), 2);

    CU_ASSERT_EQUAL(*MCV_at(vec, 0, char), 'b');
    CU_ASSERT_EQUAL(*MCV_at(vec, 1, char), 'd');
    CU_ASSERT_PTR_EQUAL(MCV_at(vec, 2, char), NULL);

    CV_delete(vec);
    free(vec);
}

void test_swap(){
    cvector* vec1 = CVector(sizeof(int), 3);
    cvector* vec2 = CVector(sizeof(char), 4);

    MCV_force_push_back(vec1, -1, int);
    MCV_force_push_back(vec2, 'a', char);
    MCV_force_push_back(vec1, 0, int);
    MCV_force_push_back(vec2, 'b', char);
    MCV_force_push_back(vec1, 1, int);
    MCV_force_push_back(vec2, 'c', char);
    MCV_force_push_back(vec1, 2, int);
    MCV_force_push_back(vec2, 'd', char);
    MCV_force_push_back(vec1, 3, int);
    MCV_force_push_back(vec2, 'e', char);
    MCV_force_push_back(vec2, 'f', char);

    CV_swap(vec1, vec2);

    CU_ASSERT_EQUAL(CV_size(vec1), 6);
    CU_ASSERT_EQUAL(CV_size(vec2), 5);

    CU_ASSERT_EQUAL(CV_capacity(vec1), 8);
    CU_ASSERT_EQUAL(CV_capacity(vec2), 6);

    CU_ASSERT_EQUAL(CV_block_size(vec1), sizeof(char));
    CU_ASSERT_EQUAL(CV_block_size(vec2), sizeof(int));

    // CU_ASSERT_EQUAL(*MCV_at())

    CV_delete(vec1);
    CV_delete(vec2);

    free(vec1);
    free(vec2);
}

void test_clear(){
    cvector* vec = CVector(sizeof(int), 1);

    for(unsigned i=0; i<10; ++i){
        CV_push_back(vec, &i);
    }
    CU_ASSERT_EQUAL(CV_size(vec), 10);
    CV_clear(vec);
    CU_ASSERT_EQUAL(CV_size(vec), 0);

    CV_delete(vec);
    free(vec);
}

void test_emplace(){
    cvector* vec = CVector(sizeof(Struct), 1);

    CU_ASSERT_PTR_EQUAL(MCV_front(vec, int), NULL);
    MCV_emplace(vec, 0, Struct, "Testing Emplace 1", 2.5);
    MCV_emplace(vec, 0, Struct, "Testing Emplace 2", 3);
    MCV_emplace(vec, 1, Struct, "Testing Emplace 3", 3.5);
    MCV_emplace(vec, 3, Struct, "Testing Emplace 4", 4);

    CU_ASSERT_EQUAL(strcmp(MCV_front(vec, Struct)->name, "Testing Emplace 2"), 0);
    CU_ASSERT_DOUBLE_EQUAL(MCV_front(vec, Struct)->weight, 3, epsilon);

    CU_ASSERT_EQUAL(strcmp(MCV_at(vec, 1, Struct)->name, "Testing Emplace 3"), 0);
    CU_ASSERT_DOUBLE_EQUAL(MCV_at(vec, 1, Struct)->weight, 3.5, epsilon);

    CU_ASSERT_EQUAL(strcmp(MCV_at(vec, 2, Struct)->name, "Testing Emplace 1"), 0);
    CU_ASSERT_DOUBLE_EQUAL(MCV_at(vec, 2, Struct)->weight, 2.5, epsilon);

    CU_ASSERT_EQUAL(strcmp(MCV_back(vec, Struct)->name, "Testing Emplace 4"), 0);
    CU_ASSERT_DOUBLE_EQUAL(MCV_back(vec, Struct)->weight, 4, epsilon);

    CV_delete(vec);
    free(vec);
}

void test_emplace_back(){
    cvector* vec = CVector(sizeof(Struct), 1);

    CU_ASSERT_PTR_EQUAL(MCV_front(vec, int), NULL);
    MCV_emplace_back(vec, Struct, "Testing Emplace Back", 2.3);
    CU_ASSERT_EQUAL(strcmp(MCV_front(vec, Struct)->name, "Testing Emplace Back"), 0);
    CU_ASSERT_DOUBLE_EQUAL(MCV_front(vec, Struct)->weight, 2.3, epsilon);

    CV_delete(vec);
    free(vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
void test_enlarge(){
    cvector* vec = CVector(sizeof(char), 1);

    CU_ASSERT_EQUAL(CV_capacity(vec), 1);
    CV_enlarge(vec, 1);
    CU_ASSERT_EQUAL(CV_capacity(vec), 1);
    CV_enlarge(vec, 2);
    CU_ASSERT_EQUAL(CV_capacity(vec), 2);
    CV_enlarge(vec, 1);
    CU_ASSERT_EQUAL(CV_capacity(vec), 2);
    CV_enlarge(vec, 2);
    CU_ASSERT_EQUAL(CV_capacity(vec), 2);
    CV_enlarge(vec, 3);
    CU_ASSERT_EQUAL(CV_capacity(vec), 3);
    CV_enlarge(vec, 3);
    CU_ASSERT_EQUAL(CV_capacity(vec), 3);
    MCV_force_push_back(vec, 'a', char);
    CV_enlarge(vec, 3);
    CU_ASSERT_EQUAL(CV_capacity(vec), 4);

    CV_delete(vec);
    free(vec);
}

void test_sort(){
    cvector* vec = CVector(sizeof(Struct), 50);
    Struct s[50];
    double weights[50];

    for(int i=0; i<50; ++i){
        s[i].weight = weights[i] = rand()%100;
        CV_push_back(vec, s+i);
    }

    MCV_sort(vec, my_sorter, Struct);
    qsort(weights, 50, sizeof(double), compare_doubles);

    for(int i=0; i<50; ++i){
        CU_ASSERT_DOUBLE_EQUAL(MCV_at(vec, i, Struct)->weight, weights[i], epsilon);
    }
    
    CV_delete(vec);
    free(vec);
}
// = = = = = = = = = = = = = = = = = = = = = = =

int main(){
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Vector Suite", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||
        
        (NULL == CU_add_test(pSuite, "test of size()", test_size)) ||
        (NULL == CU_add_test(pSuite, "test of resize()", test_resize)) ||
        (NULL == CU_add_test(pSuite, "test of capacity()", test_capacity)) ||
        (NULL == CU_add_test(pSuite, "test of empty()", test_empty)) ||
        (NULL == CU_add_test(pSuite, "test of shrink_to_fit()", test_shrink_to_fit)) ||

        (NULL == CU_add_test(pSuite, "test of at()", test_at)) ||
        (NULL == CU_add_test(pSuite, "test of front()", test_front)) ||
        (NULL == CU_add_test(pSuite, "test of back()", test_back)) ||

        (NULL == CU_add_test(pSuite, "test of push_back()", test_push_back)) ||
        (NULL == CU_add_test(pSuite, "test of pop_back()", test_pop_back)) ||
        (NULL == CU_add_test(pSuite, "test of insert()", test_insert)) ||
        (NULL == CU_add_test(pSuite, "test of erase()", test_erase)) ||
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        (NULL == CU_add_test(pSuite, "test of clear()", test_clear)) ||
        (NULL == CU_add_test(pSuite, "test of emplace()", test_emplace)) ||
        (NULL == CU_add_test(pSuite, "test of emplace_back()", test_emplace_back)) ||

        (NULL == CU_add_test(pSuite, "test of enlarge()", test_enlarge)) ||
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