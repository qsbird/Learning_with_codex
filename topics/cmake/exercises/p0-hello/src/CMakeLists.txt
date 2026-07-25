add_library(greeting SHARED)
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
target_compile_definitions(greeting
        PRIVATE
        GREETING_IMPLEMENTATION=1
)
add_library(greeting_headers INTERFACE)

target_include_directories(greeting_headers
        INTERFACE
        ${PROJECT_SOURCE_DIR}/header_only/include
)
target_compile_features(greeting
        PUBLIC
        cxx_std_17
)
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
    target_compile_options(greeting
            PRIVATE
            -Wall
            -Wextra
    )
elseif(MSVC)
    target_compile_options(greeting
            PRIVATE
            /W4
    )
endif()