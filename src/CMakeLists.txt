rock_library(sbpl_spline_primitives
    SOURCES 
            SbplSplineMotionPrimitives.cpp
    HEADERS 
            SbplSplineMotionPrimitives.hpp
            SplinePrimitivesConfig.hpp
    DEPS_PKGCONFIG 
            base-types)

add_subdirectory(gui)            
