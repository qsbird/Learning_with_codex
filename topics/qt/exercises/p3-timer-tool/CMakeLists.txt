cmake_minimum_required(VERSION 3.21)

project(p3_timer_tool LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p3_timer_tool main.cpp)

target_compile_features(p3_timer_tool PRIVATE cxx_std_17)
target_link_libraries(p3_timer_tool PRIVATE Qt6::Widgets)
