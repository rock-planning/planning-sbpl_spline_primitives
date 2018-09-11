set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

rock_testsuite(spline_motion_primitives-test suite.cpp
   test_SbplSplineMotionPrimitives.cpp
   DEPS sbpl_spline_primitives)
