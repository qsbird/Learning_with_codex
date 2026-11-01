cmake_minimum_required(VERSION 3.21)
project(systems_m0_raii LANGUAGES CXX)

include(CTest)
set(M0_SANITIZER "none" CACHE STRING "none, address, or undefined")
set_property(CACHE M0_SANITIZER PROPERTY STRINGS none address undefined)

add_library(m0_options INTERFACE)
target_compile_features(m0_options INTERFACE cxx_std_20)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(m0_options INTERFACE -Wall -Wextra -Wpedantic)
endif()
if(NOT M0_SANITIZER STREQUAL "none")
    if(NOT M0_SANITIZER MATCHES "^(address|undefined)$")
        message(FATAL_ERROR "M0_SANITIZER must be none, address, or undefined")
    endif()
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        message(FATAL_ERROR "This sanitizer configuration requires Clang or GCC")
    endif()
    target_compile_options(m0_options INTERFACE
        -fsanitize=${M0_SANITIZER} -fno-omit-frame-pointer)
    target_link_options(m0_options INTERFACE -fsanitize=${M0_SANITIZER})
    if(M0_SANITIZER STREQUAL "undefined")
        target_compile_options(m0_options INTERFACE -fno-sanitize-recover=undefined)
        target_link_options(m0_options INTERFACE -fno-sanitize-recover=undefined)
    endif()
endif()

add_library(m0_file_api STATIC support/file_api.cpp)
target_include_directories(m0_file_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/support)
target_link_libraries(m0_file_api PUBLIC m0_options)

add_library(m0_file_owner STATIC file_owner.cpp)
target_include_directories(m0_file_owner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(m0_file_owner PUBLIC m0_file_api)

add_executable(m0_fixture_check support/fixture_check.cpp)
target_link_libraries(m0_fixture_check PRIVATE m0_file_api)

add_executable(m0_raii_check tests.cpp)
target_link_libraries(m0_raii_check PRIVATE m0_file_owner)

if(BUILD_TESTING)
    add_test(NAME m0.environment COMMAND m0_fixture_check)
    add_test(NAME m0.raii COMMAND m0_raii_check)
endif()

# Reading example, kept separate from the learner-owned implementation.
add_executable(m0_scope_demo scope_trace.cpp)
target_link_libraries(m0_scope_demo PRIVATE m0_options)

# M0.1 checks are separate from the later learner-owned comprehensive baseline.
add_executable(m0_scope_check check_scope.cpp)
target_link_libraries(m0_scope_check PRIVATE m0_file_owner)
if(BUILD_TESTING)
    foreach(path IN ITEMS normal return exception empty)
        add_test(NAME m0.scope.${path} COMMAND m0_scope_check ${path})
    endforeach()
endif()
