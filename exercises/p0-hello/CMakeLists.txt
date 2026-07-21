cmake_minimum_required(VERSION 3.10)
project(hello LANGUAGES CXX)
option(HELLO_BUILD_APP
        "Build the hello application"
        ON
)
add_subdirectory(src)
if(HELLO_BUILD_APP)
    add_subdirectory(app)
endif()