cmake_minimum_required(VERSION 3.10)
project(p5_consumer LANGUAGES CXX)

# TODO(1): 以 CONFIG 模式查找已安装的 greeting 包；找不到时配置直接失败
# find_package(...)

add_executable(consumer main.cpp)

# TODO(2): 链接两个导入 target，一次拿到 include 路径、GREETING_HAS_LIBRARY 定义与 cxx_std_17
# target_link_libraries(...)
