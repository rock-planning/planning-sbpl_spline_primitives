rock_library(sbpl_spline_primitives
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(sbpl_spline_primitives_bin Main.cpp
    DEPS sbpl_spline_primitives)

