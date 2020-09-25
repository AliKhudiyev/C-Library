cmake_minimum_required(VERSION 3.10)

project(Test_C-Library)

file(GLOB SRCS ../src/*)

link_directories(/usr/local/lib)
link_libraries(cunit)
include_directories(../include /usr/local/include)

add_executable(test_vector test_vector.c ${SRCS})
add_executable(test_string test_string.c ${SRCS})
add_executable(test_set test_set.c ${SRCS})
add_executable(test_pair test_pair.c ${SRCS})