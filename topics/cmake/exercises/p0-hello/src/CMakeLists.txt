add_library(greeting SHARED)
if(GREETING_IPO_SUPPORTED)
    set_property(TARGET greeting
            PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
    )
else()
    message(STATUS "greeting IPO disabled: ${GREETING_IPO_ERROR}")
endif()
target_sources(greeting
        PRIVATE
        greeting.cpp
)
target_include_directories(greeting
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
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

target_compile_features(greeting_headers
        INTERFACE
        cxx_std_17
)
target_include_directories(greeting_headers
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/header_only/include>
        $<INSTALL_INTERFACE:include>
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
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/greeting_config.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/generated/greeting_config.h"
)

set(generated_banner_header
        "${CMAKE_CURRENT_BINARY_DIR}/generated/greeting_banner.h"
)

add_custom_command(
        OUTPUT "${generated_banner_header}"
        COMMAND "${CMAKE_COMMAND}" -E make_directory
        "${CMAKE_CURRENT_BINARY_DIR}/generated"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/greeting_banner.h.in"
        "${generated_banner_header}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/greeting_banner.h.in"
)

target_sources(greeting
        PRIVATE
        "${generated_banner_header}"
)

target_include_directories(greeting
        PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/generated"
)