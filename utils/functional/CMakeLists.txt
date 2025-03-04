project(lzl-utils-functional LANGUAGES CXX)

set(INTERFACE_HEADERS
    function_traits.h
)

# Copy library interface headers
copy_lib_i_headers(LIB lzl VERBOSE
    HEADERS_FILES
    ${INTERFACE_HEADERS}
)

# Install library interface headers
if(INSTALL_INTERFACE_HEADERS)
    install(FILES ${INTERFACE_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lzl
    )
endif()

# Add auto install post build if enable
add_auto_install_post_build_if_enable(${PROJECT_NAME})
