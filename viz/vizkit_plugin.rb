Vizkit::UiLoader.register_3d_plugin('MotionPlanningLibrariesStateVisualization', 'sbpl_spline_primitives', 'MotionPlanningLibrariesStateVisualization')
Vizkit::UiLoader.register_3d_plugin_for('MotionPlanningLibrariesStateVisualization', "/motion_planning_libraries/State", :updateData )

Vizkit::UiLoader.register_3d_plugin('Test', '', 'Test')
Vizkit::UiLoader.register_3d_plugin_for('Test', "/", :updateData )
