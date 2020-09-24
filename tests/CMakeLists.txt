cmake_minimum_required(VERSION 3.10)

project(Test_C-Library)

file(GLOB SRCS ./* ../src/*)

link_directories(/usr/local/lib)
include_directories(../include)

add_executable(test ${SRCS})
target_link_libraries(test cunit)