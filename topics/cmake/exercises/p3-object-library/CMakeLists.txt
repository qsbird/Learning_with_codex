cmake_minimum_required(VERSION 3.20)

project(object_library_demo LANGUAGES CXX)

add_library(message_objects OBJECT
        message.cpp
)

set_property(TARGET message_objects
        PROPERTY POSITION_INDEPENDENT_CODE ON
)

add_library(message_static STATIC
        $<TARGET_OBJECTS:message_objects>
)

add_library(message_shared SHARED
        $<TARGET_OBJECTS:message_objects>
)