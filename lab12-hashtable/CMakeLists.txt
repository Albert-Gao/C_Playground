cmake_minimum_required(VERSION 3.5)
project(TestGround)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ex1-war-peace.c)
add_executable(TestGround ${SOURCE_FILES})