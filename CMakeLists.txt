# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.0)
project(sbpl_spline_primitives VERSION 0.1 DESCRIPTION "Library for generating motion primitivies")
find_package(Rock)
set(ROCK_TEST_ENABLED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
rock_init()
rock_find_qt4()
rock_standard_layout()

find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(sbpl_spline_viz_bin ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
