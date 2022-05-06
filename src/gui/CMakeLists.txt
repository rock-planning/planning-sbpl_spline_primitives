rock_library(sbpl_viz_gui
    SOURCES
        SbplGui.cpp
    HEADERS
        SbplGui.h
    MOC
        SbplGui.h        
   DEPS_PKGCONFIG vizkit3d base-viz sbpl_spline_primitives-viz base-types
)

rock_executable(sbpl_spline_viz_bin
    SOURCES
        main.cpp
    DEPS sbpl_viz_gui
    DEPS_PKGCONFIG vizkit3d base-viz sbpl_spline_primitives-viz base-types)
  