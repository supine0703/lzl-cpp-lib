project(lzl-utils-functional LANGUAGES CXX)

if(FUNCTIONAL_UNUSED_GENERATED)
    if(CMAKE_CXX_STANDARD GREATER_EQUAL 17)
        set(CXX_INCLUDEDIR cxx17/)
    else()
        set(CXX_INCLUDEDIR cxx11/)
    endif()
endif()

set(INTERFACE_HEADERS
    ${CXX_INCLUDEDIR}function_traits.h
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
