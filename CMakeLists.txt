# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.0)
project(sbpl_spline_primitives VERSION 0.1 DESCRIPTION "Library for generating motion primitivies")
find_package(Rock)
set(ROCK_TEST_ENABLED ON)
rock_init()
rock_find_qt4()
rock_standard_layout()
