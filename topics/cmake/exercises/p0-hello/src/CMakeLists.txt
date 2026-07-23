add_library(greeting STATIC)
target_sources(greeting
        PRIVATE
        greeting.cpp
)
target_include_directories(greeting
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_compile_definitions(greeting
        PUBLIC
        GREETING_HAS_LIBRARY=1
)
add_library(greeting_headers INTERFACE)

target_include_directories(greeting_headers
        INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)