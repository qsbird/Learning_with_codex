add_executable(hello)
target_sources(hello
        PRIVATE
        main.cpp
)
target_link_libraries(hello
        PRIVATE
        greeting
        greeting_headers
)

if(WIN32)
    add_custom_command(TARGET hello POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:greeting>"
            "$<TARGET_FILE_DIR:hello>"
    )
endif()
