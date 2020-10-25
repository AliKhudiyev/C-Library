#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>

#include "cstring.h"

cstring *s1, *s2;

int init_suite(void){

    s1 = CString(0);
    s2 = CString(1);

    return 0;
}

int clean_suite(void){

    CS_delete(s1);
    CS_delete(s2);

    free(s1);
    free(s2);
    
    return 0;
}

// Constructor and Destructor
void test_constructor_destructor(){
    cstring* str1 = CString(0);

    CU_ASSERT_EQUAL(CS_size(str1), 0);
    CU_ASSERT_EQUAL(CS_capacity(str1), 1);

    CS_delete(str1);
    free(str1);
    
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
    
    CS_erase(&str, 1);
    CU_ASSERT_EQUAL(CS_size(&str), 8);

    CS_replace(&str, 1, 1, "_B_");
    CU_ASSERT_EQUAL(CS_size(&str), 10);

    CS_assign(&str, "ABCDEFGH", 5);
    CU_ASSERT_EQUAL(CS_size(&str), 6);

    CS_delete(&str);
}

void test_resize(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT_EQUAL(CS_capacity(&str), 1);

    CS_resize(&str, 10);
    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT_EQUAL(CS_capacity(&str), 10);

    CS_resize(&str, 5);
    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT_EQUAL(CS_capacity(&str), 10);

    CS_resize(&str, 0);
    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT_EQUAL(CS_capacity(&str), 10);

    CS_destruct(&str);
}

void test_capacity(){
    cstring str;
    CS_init(&str, 0);

    CU_ASSERT_EQUAL(CS_capacity(&str), 1);

    CS_assign(&str, "ABCDEFGH", 2);
    CU_ASSERT_EQUAL(CS_capacity(&str), 4);

    CS_assign(&str, "ABCDEFGH", 7);
    CU_ASSERT_EQUAL(CS_capacity(&str), 14);

    CS_destruct(&str);
}
void test_reserve(){
    CU_ASSERT(1);
}

void test_clear(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT(CS_empty(&str));

    CS_clear(&str);
    CU_ASSERT(CS_empty(&str));

    CS_assign(&str, "Hello", -1);
    CS_clear(&str);
    CU_ASSERT(CS_empty(&str));

    CS_append(&str, "Hello", -1);
    CS_clear(&str);
    CU_ASSERT(CS_empty(&str));

    CS_destruct(&str);
}

void test_empty(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT(CS_empty(&str));

    CS_append(&str, "ABC", -1);
    CU_ASSERT(!CS_empty(&str));

    CS_assign(&str, "", -1);
    CU_ASSERT(CS_empty(&str));

    CS_delete(&str);
}

void test_shrink_to_fit(){
    cstring str;
    CS_init(&str, 30);

    CS_assign(&str, "Hello!", -1);
    CS_replace(&str, 5, 1, ", World!");
    CU_ASSERT_EQUAL(CS_capacity(&str), 30);
    
    CS_shrink_to_fit(&str);
    CU_ASSERT_EQUAL(CS_capacity(&str), CS_size(&str));

    CS_destruct(&str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Element access
void test_at(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT_EQUAL(CS_at(&str, 0), 0);
    CU_ASSERT_EQUAL(CS_at(&str, 1), 0);
    CU_ASSERT_EQUAL(CS_at(&str, -1), 0);

    CS_append(&str, "ABC", 3);
    CU_ASSERT_EQUAL(CS_at(&str, 0), 'A');
    CU_ASSERT_EQUAL(CS_at(&str, 1), 'B');
    CU_ASSERT_EQUAL(CS_at(&str, 2), 'C');
    CU_ASSERT_EQUAL(CS_at(&str, 3), 0);
    CU_ASSERT_EQUAL(CS_at(&str, -1), 0);

    CS_append(&str, "D", 3);
    CU_ASSERT_EQUAL(CS_at(&str, 0), 'A');
    CU_ASSERT_EQUAL(CS_at(&str, 1), 'B');
    CU_ASSERT_EQUAL(CS_at(&str, 2), 'C');
    CU_ASSERT_EQUAL(CS_at(&str, 3), 'D');
    CU_ASSERT_EQUAL(CS_at(&str, 4), 0);
    CU_ASSERT_EQUAL(CS_at(&str, -1), 0);

    CS_destruct(&str);
}

void test_front(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT_EQUAL(CS_front(&str), 0);

    CS_assign(&str, "world", -1);
    CU_ASSERT_EQUAL(CS_front(&str), 'w');

    CS_insert(&str, 0, "Hello, ", -1);
    CU_ASSERT_EQUAL(CS_front(&str), 'H');

    CS_append(&str, "!", 1);
    CU_ASSERT_EQUAL(CS_front(&str), 'H');

    CS_destruct(&str);
}

void test_back(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT_EQUAL(CS_back(&str), 0);

    CS_assign(&str, "world", -1);
    CU_ASSERT_EQUAL(CS_back(&str), 'd');

    CS_insert(&str, 0, "Hello, ", -1);
    CU_ASSERT_EQUAL(CS_front(&str), 'd');

    CS_append(&str, "!", 1);
    CU_ASSERT_EQUAL(CS_front(&str), '!');

    CS_destruct(&str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// Modifiers
void test_append(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "ABC", 2);
    CU_ASSERT(!strcmp(CS_c_str(&str), "AB"));

    CS_append(&str, "ABC", 5);
    CU_ASSERT(!strcmp(CS_c_str(&str), "ABABC"));

    CS_append(&str, "ABC", -1);
    CU_ASSERT(!strcmp(CS_c_str(&str), "ABABCABC"));

    CS_destruct(&str);
}

void test_push_back(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "ABC", 2);
    CU_ASSERT(!strcmp(CS_c_str(&str), "AB"));

    CS_push_back(&str, 'C');
    CU_ASSERT(!strcmp(CS_c_str(&str), "ABC"));

    CS_push_back(&str, 'D');
    CU_ASSERT(!strcmp(CS_c_str(&str), "ABCD"));

    CS_destruct(&str);
}

void test_assign(){
    cstring str;
    CS_init(&str, 1);

    CS_assign(&str, "Hello", -1);
    CU_ASSERT(!strncmp("Hello", CS_c_str(&str), strlen("Hello")));

    CS_assign(&str, "ABC", 2);
    CU_ASSERT(!strncmp("ABC", CS_c_str(&str), 2));

    CS_assign(&str, "DEF", 3);
    CU_ASSERT(!strncmp("DEF", CS_c_str(&str), 3));

    CS_assign(&str, "?", 2);
    CU_ASSERT(!strncmp("?", CS_c_str(&str), strlen("?")));

    CS_assign(&str, "", -1);
    CU_ASSERT(CS_empty(&str));

    CS_destruct(&str);
}

void test_insert(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "ABC", 2);
    CU_ASSERT(!strcmp(CS_c_str(&str), "AB"));

    CS_insert(&str, 0, "CD", 5);
    CU_ASSERT(!strcmp(CS_c_str(&str), "CDAB"));

    CS_insert(&str, 1, "EFG", -1);
    CU_ASSERT(!strcmp(CS_c_str(&str), "CEFGDAB"));

    CS_destruct(&str);
}

void test_erase(){
    cstring str;
    CS_init(&str, 1);

    CS_erase(&str, 0);
    CS_erase(&str, -1);

    CS_append(&str, "ABCDEFGH", -1);

    CS_erase(&str, 0);
    CU_ASSERT(!strcmp(CS_c_str(&str), "BCDEFGH"));

    CS_erase(&str, 1);
    CU_ASSERT(!strcmp(CS_c_str(&str), "BDEFGH"));

    CS_destruct(&str);
}

void test_replace(){
    cstring str;
    CS_init(&str, 1);

    CS_erase(&str, 0);
    CS_erase(&str, -1);

    CS_append(&str, "Hello, programmer!", -1);

    CS_replace(&str, 6, 11, " World");
    CU_ASSERT(!strcmp(CS_c_str(&str), "Hello, World!"));

    CS_destruct(&str);
}

void test_swap(){
    cstring str1, str2;

    CS_init(&str1, 1);
    CS_init(&str2, 1);

    CS_assign(&str1, "Hello", -1);
    CS_assign(&str2, "C-Library", -1);

    CS_swap(&str1, &str2);

    CU_ASSERT(!strcmp(CS_c_str(&str1), "C-Library"));
    CU_ASSERT(!strcmp(CS_c_str(&str2), "Hello"));

    CS_destruct(&str1);
    CS_destruct(&str2);
}

void test_pop_back(){
    cstring str;
    CS_init(&str, 1);

    CS_assign(&str, "ABC", -1);
    CU_ASSERT_EQUAL(CS_size(&str), 4);
    CU_ASSERT(!strcmp(CS_c_str(&str), "ABC"));

    CS_pop_back(&str);
    CU_ASSERT_EQUAL(CS_size(&str), 3);
    CU_ASSERT(!strcmp(CS_c_str(&str), "AB"));

    CS_pop_back(&str);
    CU_ASSERT_EQUAL(CS_size(&str), 2);
    CU_ASSERT(!strcmp(CS_c_str(&str), "A"));

    CS_pop_back(&str);
    CU_ASSERT_EQUAL(CS_size(&str), 1);
    CU_ASSERT(!strcmp(CS_c_str(&str), ""));

    CS_pop_back(&str);
    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT(CS_empty(&str));

    CS_pop_back(&str);
    CU_ASSERT_EQUAL(CS_size(&str), 0);
    CU_ASSERT(CS_empty(&str));

    CS_destruct(&str);
}
// = = = = = = = = = = = = = = = = = = = = = = =

// String operations
void test_c_str(){
    cstring str;
    CS_init(&str, 1);

    CU_ASSERT(!CS_c_str(&str));

    CS_assign(&str, "ABC", -1);
    CU_ASSERT_PTR_EQUAL(CS_begin(&str), CS_c_str(&str));

    CS_destruct(&str);
}

void test_data(){
    cstring str;
    CS_init(&str, 1);

    CS_append(&str, "AB", -1);

    char* iterator = CS_data(&str);

    CU_ASSERT_EQUAL(CS_front(&str), iterator[0]);
    CU_ASSERT_EQUAL(CS_at(&str, 1), iterator[1]);
    CU_ASSERT_EQUAL(CS_back(&str), iterator[2]);
    CU_ASSERT_EQUAL(iterator[2], 0);

    CS_destruct(&str);
}

void test_copy(){
    cstring str, str_copy;
    CS_init(&str, 1);
    CS_init(&str_copy, 1);

    CS_assign(&str, "Original", -1);
    CS_assign(&str_copy, "Copy", -1);

    CS_assign(&str_copy, CS_c_str(&str), -1);

    CU_ASSERT_EQUAL(CS_size(&str_copy), CS_size(&str));
    CU_ASSERT_EQUAL(CS_capacity(&str_copy), CS_capacity(&str));
    CU_ASSERT(!strcmp(CS_c_str(&str_copy), CS_c_str(&str)));

    CS_destruct(&str);
    CS_destruct(&str_copy);
}

void test_find(){
    cstring str;
    CS_init(&str, 1);

    CS_assign(&str, "Hello, young programmer!", -1);

    CU_ASSERT_EQUAL(CS_find(&str, "young ", 0), 7);
    CU_ASSERT_EQUAL(CS_find(&str, " ", 0), 6);

    CU_ASSERT_EQUAL(CS_find(&str, "young", 7), 0);
    CU_ASSERT_EQUAL(CS_find(&str, " ", 5), 1);

    CU_ASSERT_EQUAL(CS_find(&str, "young", 8), (size_t)-1);
    CU_ASSERT_EQUAL(CS_find(&str, " ", 7), 5);

    CU_ASSERT_EQUAL(CS_find(&str, "young  a", 0), (size_t)-1);
    CU_ASSERT_EQUAL(CS_find(&str, " ", -1), (size_t)-1);

    CS_destruct(&str);
}

void test_rfind(){
    cstring str;
    CS_init(&str, 1);

    CS_assign(&str, "Hello, young programmer!", -1);
    
    CU_ASSERT_EQUAL(CS_rfind(&str, "young ", 0), 16);
    CU_ASSERT_EQUAL(CS_rfind(&str, " ", 0), 11);

    CU_ASSERT_EQUAL(CS_rfind(&str, "young", 8), (size_t)-1);
    CU_ASSERT_EQUAL(CS_rfind(&str, " ", 13), (size_t)-1);

    CU_ASSERT_EQUAL(CS_rfind(&str, "young  ", 8), (size_t)-1);
    CU_ASSERT_EQUAL(CS_rfind(&str, "!", 7), 0);

    CU_ASSERT_EQUAL(CS_rfind(&str, "young  a", 0), (size_t)-1);
    CU_ASSERT_EQUAL(CS_rfind(&str, " ", -1), (size_t)-1);

    CS_destruct(&str);
}

void test_find_first_of(){
    cstring str;
    CS_init(&str, 1);

    // TO DO

    CS_destruct(&str);
}

void test_find_last_of(){
    cstring str;
    CS_init(&str, 1);

    // TO DO

    CS_destruct(&str);
}

void test_find_first_not_of(){
    cstring str;
    CS_init(&str, 1);

    // TO DO

    CS_destruct(&str);
}

void test_find_last_not_of(){
    cstring str;
    CS_init(&str, 1);

    // TO DO

    CS_destruct(&str);
}

void test_substr(){
    cstring str;
    CS_init(&str, 1);

    CS_assign(&str, "Hello, young programmer!", -1);

    cstring* substr1 = CS_substr(&str, 7, 5);
    cstring* substr2 = CS_substr(&str, 0, -1);
    cstring* substr3 = CS_substr(&str, -1, 5);

    CU_ASSERT(!strcmp(CS_c_str(substr1), "young"));
    CU_ASSERT(!strcmp(CS_c_str(substr2), "Hello, young programmer!"));
    CU_ASSERT_PTR_EQUAL(substr3, NULL);

    CS_destruct(&str);

    CS_destruct(substr1);
    CS_destruct(substr2);
    CS_destruct(substr3);

    free(substr1);
    free(substr2);
    free(substr3);
}

void test_compare(){
    cstring str1, str2;

    CS_init(&str1, 1);
    CS_init(&str2, 1);

    CS_assign(&str1, "Hello, C-Library!", -1);
    CS_assign(&str2, "Hello, World!", -1);

    CU_ASSERT_EQUAL(CS_compare(&str1, &str2, 0), 0);
    CU_ASSERT_EQUAL(CS_compare(&str1, &str2, 7), 0);
    CU_ASSERT_EQUAL(CS_compare(&str1, &str2, 8), -1);
    CU_ASSERT_EQUAL(CS_compare(&str1, &str2, -1), 1);

    CS_destruct(&str1);
    CS_destruct(&str2);
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