cmake_minimum_required(VERSION 3.10)
project(hello LANGUAGES CXX)
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
add_subdirectory(src)
if(HELLO_BUILD_APP)
    add_subdirectory(app)
endif()