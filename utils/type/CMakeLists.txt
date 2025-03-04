project(lzl-utils-type LANGUAGES CXX)

# Copy library interface headers
copy_lib_i_headers(LIB lzl VERBOSE
    HEADERS_FILES
    typename.h
)
copy_lib_i_headers(LIB lzl/cxx11 VERBOSE
    HEADERS_FILES
    cxx11/maybe_lambda.h
    cxx11/typename.h
)
copy_lib_i_headers(LIB lzl/cxx17 VERBOSE
    HEADERS_FILES
    cxx17/maybe_lambda.h
    cxx17/typename.h
)

# Install library interface headers
if(INSTALL_INTERFACE_HEADERS)
    install(FILES typename.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lzl
    )
    install(FILES cxx11/maybe_lambda.h cxx11/typename.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lzl/cxx11
    )
    install(FILES cxx17/maybe_lambda.h cxx17/typename.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lzl/cxx17
    )
endif()

# Add auto install post build if enable
add_auto_install_post_build_if_enable(${PROJECT_NAME})
