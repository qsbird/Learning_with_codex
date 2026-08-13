cmake_minimum_required(VERSION 3.21)

project(p2_click_label LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p2_click_label main.cpp)

target_compile_features(p2_click_label PRIVATE cxx_std_17)
target_link_libraries(p2_click_label PRIVATE Qt6::Widgets)
