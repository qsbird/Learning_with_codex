cmake_minimum_required(VERSION 3.21)
project(p1_widget_shell LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(p1_widget_shell
    main.cpp
    mainwindow.ui
    icons.qrc   # 新：和 .ui 一样列入源文件
)

target_compile_features(p1_widget_shell PRIVATE cxx_std_17)
target_link_libraries(p1_widget_shell PRIVATE Qt6::Widgets)