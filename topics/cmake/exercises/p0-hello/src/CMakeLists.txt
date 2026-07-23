add_library(greeting STATIC)
target_sources(greeting
        PRIVATE
        greeting.cpp
)
target_include_directories(greeting
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)