cmake_minimum_required(VERSION 3.21)

project(qt_learning_workspace LANGUAGES CXX)

# Stable IDE entry point. Each exercise remains independently configurable.
set(QT_LEARNING_EXERCISES
    p0-hello-widget
    p1-widget-shell
    p2-click-label
    p3-layout-form
    p3-timer-tool
)

foreach(exercise IN LISTS QT_LEARNING_EXERCISES)
    set(exercise_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/exercises/${exercise}")

    # Allow an in-progress local lesson to be listed before it is published.
    if(EXISTS "${exercise_source_dir}/CMakeLists.txt")
        add_subdirectory("${exercise_source_dir}" "exercises/${exercise}")
    endif()
endforeach()
