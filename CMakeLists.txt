cmake_minimum_required(VERSION 3.10)

project(C-Library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(main main.c ${SRCS})