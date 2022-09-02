find_package(Boost COMPONENTS system filesystem REQUIRED)

rock_library(sbpl_viz_gui
    SOURCES
        SbplGui.cpp
    HEADERS
        SbplGui.h
    MOC
        SbplGui.h
    DEPS sbpl_spline_primitives-viz
    DEPS_PKGCONFIG vizkit3d base-types vizkit3d-viz base-viz 
)

target_include_directories(sbpl_viz_gui PRIVATE ${CMAKE_SOURCE_DIR}/viz)

rock_executable(sbpl_spline_viz_bin
    SOURCES
        main.cpp
    DEPS sbpl_viz_gui)

target_link_libraries(sbpl_spline_viz_bin ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})    
