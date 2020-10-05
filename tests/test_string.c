#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "cstring.h"

double epsilon = 1e-6;

typedef struct{
    char name[30];
    double weight;
}Struct;

cstring *s1, *s2;

int my_sorter(Struct s1, Struct s2){
    return s1.weight >= s2.weight;
}

int compare_doubles(const void* a, const void* b){
    // return *(double*)a >= *(double*)b;
    return *(double*)a - *(double*)b;
}

int init_suite(void){
    s1 = CString(0);
    s2 = CString(1);

    return 0;
}

int clean_suite(void){
    CS_delete(s1);
    CS_delete(s2);
    
    return 0;
}

// Constructor and Destructor
void test_constructor_destructor(){
    cstring* str1 = CString(0);

    CU_ASSERT_EQUAL(CS_size(str1), 0);
    CU_ASSERT_EQUAL(CS_capacity(str1), 1);

    CS_delete(str1);
    
    for(size_t i=0; i<10; ++i){
        cstring str2;
        CS_init(&str2, i);
        
        CU_ASSERT_EQUAL(CS_size(&str2), 0);
        CU_ASSERT_EQUAL(CS_capacity(&str2), i? i : 1);

        CS_delete(&str2);
    }
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Iterators
void test_begin(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "ABC", -1);
    CU_ASSERT_EQUAL(*CS_begin(&str), 'A');

    CS_delete(&str);
}

void test_end(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "ABC", -1);
    CU_ASSERT_EQUAL(*CS_end(&str), '\0');

    CS_delete(&str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Capacity
void test_size(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CS_append(&str, "ABC", 2);
    CU_ASSERT_EQUAL(CS_size(&str), 3);
    CS_push_back(&str, 'D');
    CU_ASSERT_EQUAL(CS_size(&str), 4);
    CS_append(&str, "EFG", -1);
    CU_ASSERT_EQUAL(CS_size(&str), 7);
    CS_append(&str, "HK", 5);
    CU_ASSERT_EQUAL(CS_size(&str), 9);

    CS_delete(&str);
}

void test_resize(){
    ;
}

void test_capacity(){
    ;
}
void test_reserve(){
    ;
}

void test_clear(){
    ;
}

void test_empty(){
    ;
}

void test_shrink_to_fit(){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void test_at(){
    ;
}

void test_front(){
    ;
}

void test_back(){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void test_append(){
    ;
}

void test_push_back(){
    ;
}

void test_assign(){
    ;
}

void test_insert(){
    ;
}

void test_erase(){
    ;
}

void test_replace(){
    ;
}

void test_swap(){
    ;
}

void test_pop_back(){
    ;
}
// = = = = = = = = = = = = = = = = = = = = = = =

// String operations
void test_c_str(){
    ;
}

void test_data(){
    ;
}

void test_copy(){
    ;
}

void test_find(){
    ;
}

void test_rfind(){
    ;
}

void test_find_first_of(){
    ;
}

void test_find_last_of(){
    ;
}

void test_find_first_not_of(){
    ;
}

void test_find_last_not_of(){
    ;
}

void test_substr(){
    ;
}

void test_compare(){
    ;
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
    pSuite = CU_add_suite("String Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of constructor and destructor", test_constructor_destructor)) ||
        
        (NULL == CU_add_test(pSuite, "test of begin()", test_begin)) ||
        (NULL == CU_add_test(pSuite, "test of end()", test_end)) ||
        
        (NULL == CU_add_test(pSuite, "test of size()", test_size)) ||
        (NULL == CU_add_test(pSuite, "test of resize()", test_resize)) ||
        (NULL == CU_add_test(pSuite, "test of capacity()", test_capacity)) ||
        (NULL == CU_add_test(pSuite, "test of reserve()", test_reserve)) ||
        (NULL == CU_add_test(pSuite, "test of clear()", test_clear)) ||
        (NULL == CU_add_test(pSuite, "test of empty()", test_empty)) ||
        (NULL == CU_add_test(pSuite, "test of shrink_to_fit()", test_shrink_to_fit)) ||
        
        (NULL == CU_add_test(pSuite, "test of at()", test_at)) ||
        (NULL == CU_add_test(pSuite, "test of front()", test_front)) ||
        (NULL == CU_add_test(pSuite, "test of back()", test_begin)) ||
        
        (NULL == CU_add_test(pSuite, "test of append()", test_append)) ||
        (NULL == CU_add_test(pSuite, "test of push_back()", test_push_back)) ||
        (NULL == CU_add_test(pSuite, "test of assign()", test_assign)) ||
        (NULL == CU_add_test(pSuite, "test of insert()", test_insert)) ||
        (NULL == CU_add_test(pSuite, "test of erase()", test_erase)) ||
        (NULL == CU_add_test(pSuite, "test of replace()", test_replace)) ||
        (NULL == CU_add_test(pSuite, "test of swap()", test_swap)) ||
        (NULL == CU_add_test(pSuite, "test of pop_back()", test_pop_back)) ||

        (NULL == CU_add_test(pSuite, "test of c_str()", test_c_str)) ||
        (NULL == CU_add_test(pSuite, "test of data()", test_data)) ||
        (NULL == CU_add_test(pSuite, "test of copy()", test_copy)) ||
        (NULL == CU_add_test(pSuite, "test of find()", test_find)) ||
        (NULL == CU_add_test(pSuite, "test of rfind()", test_rfind)) ||
        (NULL == CU_add_test(pSuite, "test of find_first_of()", test_find_first_of)) ||
        (NULL == CU_add_test(pSuite, "test of find_last_of()", test_find_last_of)) ||
        (NULL == CU_add_test(pSuite, "test of find_first_not_of()", test_find_first_not_of)) ||
        (NULL == CU_add_test(pSuite, "test of find_last_not_of()", test_find_last_not_of)) ||
        (NULL == CU_add_test(pSuite, "test of substr()", test_substr)) ||
        (NULL == CU_add_test(pSuite, "test of compare()", test_compare)))
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