rock_library(sbpl_viz_gui
    SOURCES
        SbplGui.cpp
    HEADERS
        SbplGui.h
    MOC
        SbplGui.h
   DEPS sbpl_spline_primitives-viz
   DEPS_PKGCONFIG vizkit3d base-viz base-types
)

rock_executable(sbpl_spline_viz_bin
    SOURCES
        main.cpp
    DEPS sbpl_viz_gui)
