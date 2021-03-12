#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "cset.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

cset *s1, *s2;

int init_suite(void){

    s1 = CSet(sizeof(Struct), 1);
    s2 = CSet(sizeof(double), 1);

    return 0;
}

int clean_suite(void){

    CSet_delete(s1);
    CSet_delete(s2);

    free(s1);
    free(s2);
    
    return 0;
}

// Constructor and Destructor
void test_constructor_destructor(){
    cset* set = CSet(sizeof(char), 0);

    CU_ASSERT_EQUAL(CSet_size(set), 0);
    CU_ASSERT_EQUAL(CSet_max_size(set), 1);
    CU_ASSERT(CSet_empty(set));

    CSet_delete(set);
    free(set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void test_begin(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_PTR_EQUAL(CSet_begin(&set), CSet_end(&set));

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_end(&set)-CSet_begin(&set), sizeof(int));

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_NOT_EQUAL(CSet_begin(&set), CSet_end(&set));
    CU_ASSERT_EQUAL(CSet_end(&set)-CSet_begin(&set), 2*sizeof(int));

    CSet_destruct(&set);
}

void test_end(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_PTR_EQUAL(CSet_begin(&set), CSet_end(&set));

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_end(&set)-CSet_begin(&set), sizeof(int));

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_NOT_EQUAL(CSet_begin(&set), CSet_end(&set));
    CU_ASSERT_EQUAL(CSet_end(&set)-CSet_begin(&set), 2*sizeof(int));

    CSet_destruct(&set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
void test_empty(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT(CSet_empty(&set));

    MCSet_emplace(&set, int, 3);
    CU_ASSERT(!CSet_empty(&set));

    CSet_clear(&set);
    CU_ASSERT(CSet_empty(&set));

    CSet_destruct(&set);
}

void test_size(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_EQUAL(CSet_size(&set), 0);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_size(&set), 1);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_size(&set), 1);

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_EQUAL(CSet_size(&set), 2);

    CSet_clear(&set);
    CU_ASSERT(CSet_empty(&set));
    CU_ASSERT_EQUAL(CSet_size(&set), 0);

    CSet_destruct(&set);
}

void test_max_size(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_EQUAL(CSet_max_size(&set), 1);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 1);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 1);

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 2);

    MCSet_emplace(&set, int, 0);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 4);

    CSet_clear(&set);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 4);

    CSet_destruct(&set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void test_at(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_PTR_EQUAL(CSet_at(&set, 0), NULL);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, -1), NULL);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(*(int*)CSet_at(&set, 0), 3);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, -1), NULL);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_PTR_NOT_EQUAL(CSet_at(&set, 0), NULL);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, -1), NULL);

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_EQUAL(*(int*)CSet_at(&set, 0), 3);
    CU_ASSERT_EQUAL(*(int*)CSet_at(&set, 1), 5);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, 2), NULL);

    CSet_clear(&set);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, 0), NULL);
    CU_ASSERT_PTR_EQUAL(CSet_at(&set, -1), NULL);

    CSet_destruct(&set);
}

void test_front(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_PTR_EQUAL(CSet_front(&set), NULL);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(*(int*)CSet_front(&set), 3);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_PTR_NOT_EQUAL(CSet_front(&set), NULL);

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_EQUAL(*(int*)CSet_front(&set), 3);

    CSet_clear(&set);
    CU_ASSERT_PTR_EQUAL(CSet_front(&set), NULL);

    CSet_destruct(&set);
}

void test_back(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT_PTR_EQUAL(CSet_back(&set), NULL);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_EQUAL(*(int*)CSet_back(&set), 3);

    MCSet_emplace(&set, int, 3);
    CU_ASSERT_PTR_NOT_EQUAL(CSet_back(&set), NULL);

    MCSet_emplace(&set, int, 5);
    CU_ASSERT_EQUAL(*(int*)CSet_back(&set), 5);

    CSet_clear(&set);
    CU_ASSERT_PTR_EQUAL(CSet_back(&set), NULL);

    CSet_destruct(&set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void test_insert(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CU_ASSERT(CSet_empty(&set));

    MCSet_emplace(&set, int, 0);
    CU_ASSERT_EQUAL(*MCSet_front(&set, int), 0);

    MCSet_emplace(&set, int, 0*1);
    CU_ASSERT_EQUAL(*MCSet_front(&set, int), 0);

    MCSet_emplace(&set, int, 1);
    CU_ASSERT_EQUAL(*MCSet_front(&set, int), 0);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 1, int), 1);

    MCSet_emplace(&set, int, 0-1);
    CU_ASSERT_EQUAL(*MCSet_front(&set, int), 0);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 1, int), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 2, int), -1);

    CSet_destruct(&set);
}

void test_erase(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    MCSet_force_erase(&set, int, 10);
    CU_ASSERT_EQUAL(CSet_size(&set), 0);

    MCSet_emplace(&set, int, 0);
    MCSet_emplace(&set, int, 1);
    MCSet_emplace(&set, int, 2);
    MCSet_force_erase(&set, int, -1);
    CU_ASSERT_EQUAL(CSet_size(&set), 3);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 0, int), 0);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 1, int), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 2, int), 2);

    MCSet_force_erase(&set, int, 0);
    CU_ASSERT_EQUAL(CSet_size(&set), 2);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 0, int), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 1, int), 2);

    MCSet_force_erase(&set, int, 0);
    CU_ASSERT_EQUAL(CSet_size(&set), 2);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 0, int), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 1, int), 2);

    MCSet_force_erase(&set, int, 2);
    CU_ASSERT_EQUAL(CSet_size(&set), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 0, int), 1);

    MCSet_emplace(&set, int, 2);
    MCSet_force_erase(&set, int, 1);
    CU_ASSERT_EQUAL(CSet_size(&set), 1);
    CU_ASSERT_EQUAL(*MCSet_at(&set, 0, int), 2);

    CSet_destruct(&set);
}

void test_swap(){
    cset set1, set2;
    CSet_init(&set1, sizeof(int), 1);
    CSet_init(&set2, sizeof(char), 1);

    MCSet_emplace(&set1, int, 1);
    MCSet_emplace(&set1, int, 2);
    MCSet_emplace(&set1, int, 3);

    MCSet_emplace(&set2, char, 'A');
    MCSet_emplace(&set2, char, 'B');
    MCSet_emplace(&set2, char, 'a');
    MCSet_emplace(&set2, char, 'b');

    CSet_swap(&set1, &set2);

    CU_ASSERT_EQUAL(CSet_size(&set1), 4);
    CU_ASSERT_EQUAL(CSet_max_size(&set1), 4);

    CU_ASSERT_EQUAL(CSet_size(&set2), 3);
    CU_ASSERT_EQUAL(CSet_max_size(&set2), 4);

    CSet_destruct(&set1);
    CSet_destruct(&set2);
}

void test_clear(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    CSet_clear(&set);
    CU_ASSERT(CSet_empty(&set));
    CU_ASSERT_EQUAL(CSet_max_size(&set), 1);

    MCSet_emplace(&set, int, 0);
    MCSet_emplace(&set, int, 1);
    MCSet_emplace(&set, int, 2);
    CU_ASSERT(!CSet_empty(&set));
    CU_ASSERT_EQUAL(CSet_size(&set), 3);
    CU_ASSERT_EQUAL(CSet_max_size(&set), 4);

    CSet_clear(&set);
    CU_ASSERT(CSet_empty(&set));
    CU_ASSERT_EQUAL(CSet_max_size(&set), 4);

    CSet_destruct(&set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Operations
void test_find(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    size_t result;
    MCSet_force_find(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    MCSet_emplace(&set, int, 0);
    MCSet_emplace(&set, int, -1);
    MCSet_emplace(&set, int, 23);
    MCSet_force_find(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, 0);

    MCSet_force_find(&set, result, int, -1);
    CU_ASSERT_EQUAL(result, 1);

    MCSet_force_find(&set, result, int, 23);
    CU_ASSERT_EQUAL(result, 2);

    CSet_clear(&set);
    
    MCSet_force_find(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    MCSet_force_find(&set, result, int, -1);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    MCSet_force_find(&set, result, int, 23);
    CU_ASSERT_EQUAL(result, (size_t)-1);

    CSet_destruct(&set);
}

void test_count(){
    cset set;
    CSet_init(&set, sizeof(int), 1);

    size_t result;
    MCSet_force_count(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, 0);

    MCSet_emplace(&set, int, 0);
    MCSet_emplace(&set, int, -1);
    MCSet_emplace(&set, int, 23);
    MCSet_force_count(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, 1);

    MCSet_force_count(&set, result, int, -1);
    CU_ASSERT_EQUAL(result, 1);

    MCSet_force_count(&set, result, int, 23);
    CU_ASSERT_EQUAL(result, 1);

    CSet_clear(&set);
    
    MCSet_force_count(&set, result, int, 0);
    CU_ASSERT_EQUAL(result, 0);

    MCSet_force_count(&set, result, int, -1);
    CU_ASSERT_EQUAL(result, 0);

    MCSet_force_count(&set, result, int, 23);
    CU_ASSERT_EQUAL(result, 0);

    CSet_destruct(&set);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Additional
// = = = = = = = = = = = = = = = = = = = = = = =

int main(){
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Set Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||

        (NULL == CU_add_test(pSuite, "test of begin()", test_begin)) ||
        (NULL == CU_add_test(pSuite, "test of end()", test_end)) ||
        
        (NULL == CU_add_test(pSuite, "test of empty()", test_empty)) ||
        (NULL == CU_add_test(pSuite, "test of size()", test_size)) ||
        (NULL == CU_add_test(pSuite, "test of max_size()", test_max_size)) ||

        (NULL == CU_add_test(pSuite, "test of at()", test_at)) ||
        (NULL == CU_add_test(pSuite, "test of front()", test_front)) ||
        (NULL == CU_add_test(pSuite, "test of back()", test_back)) ||

        (NULL == CU_add_test(pSuite, "test of insert()", test_insert)) ||
        (NULL == CU_add_test(pSuite, "test of erase()", test_erase)) ||
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        (NULL == CU_add_test(pSuite, "test of clear()", test_clear)) ||

        (NULL == CU_add_test(pSuite, "test of find()", test_find)) ||
        (NULL == CU_add_test(pSuite, "test of count()", test_count)))
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