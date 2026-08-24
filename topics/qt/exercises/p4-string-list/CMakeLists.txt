cmake_minimum_required(VERSION 3.21)

project(p4_string_list LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p4_string_list main.cpp)

target_compile_features(p4_string_list PRIVATE cxx_std_17)
target_link_libraries(p4_string_list PRIVATE Qt6::Widgets)
