cmake_minimum_required(VERSION 3.21)

project(p3_layout_form LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p3_layout_form main.cpp)

target_compile_features(p3_layout_form PRIVATE cxx_std_17)
target_link_libraries(p3_layout_form PRIVATE Qt6::Widgets)
