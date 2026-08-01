cmake_minimum_required(VERSION 3.10)
project(hello LANGUAGES CXX)
enable_testing()
include(CheckIncludeFileCXX)
check_include_file_cxx("unistd.h" HAVE_UNISTD_H)
include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    #include <unistd.h>
    int main() {
        return getpid() == -1;
    }
" HAVE_GETPID)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(HelloOptions)
include(CheckIPOSupported)

check_ipo_supported(
        RESULT GREETING_IPO_SUPPORTED
        OUTPUT GREETING_IPO_ERROR
        LANGUAGES CXX
)

message(STATUS "GREETING_IPO_SUPPORTED=${GREETING_IPO_SUPPORTED}")


add_subdirectory(src)
if(HELLO_BUILD_APP)
    add_subdirectory(app)
    add_test(
            NAME hello_smoke
            COMMAND hello
    )
    set_tests_properties(hello_smoke PROPERTIES
            PASS_REGULAR_EXPRESSION "Hello World from program input"
    )
endif()


install(TARGETS greeting
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
install(DIRECTORY include/
        DESTINATION include
)
install(DIRECTORY header_only/include/
        DESTINATION include
)