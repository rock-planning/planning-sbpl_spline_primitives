# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 2.6)
find_package(Rock)
set(ROCK_TEST_ENABLED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
rock_init(sbpl_spline_primitives 0.1)
rock_standard_layout()

find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(sbpl_spline_viz_bin ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
