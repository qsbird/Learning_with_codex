cmake_minimum_required(VERSION 3.21)

project(p4_readonly_table LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p4_readonly_table
    main.cpp
    resultmodel.cpp
    resultmodel.h
)

target_compile_features(p4_readonly_table PRIVATE cxx_std_17)
target_link_libraries(p4_readonly_table PRIVATE Qt6::Widgets)
