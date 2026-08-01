cmake_minimum_required(VERSION 3.21)

project(p0_hello_widget LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p0_hello_widget main.cpp)

target_compile_features(p0_hello_widget PRIVATE cxx_std_17)
target_link_libraries(p0_hello_widget PRIVATE Qt6::Widgets)
