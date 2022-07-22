# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.0)
project(sbpl_spline_primitives VERSION 0.1 DESCRIPTION "Library for generating motion primitivies")
find_package(Rock)
set(ROCK_TEST_ENABLED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
rock_init()
rock_standard_layout()
