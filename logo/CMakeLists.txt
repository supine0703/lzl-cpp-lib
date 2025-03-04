# License: MIT
# Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
# Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>

# Generate logo header file
set(INTERFACE_HEADERS logo.h)
set(LZL_CPP_LIB_LOGO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERFACE_HEADERS})
set(LZL_CPP_LIB_LOGO_VALUE "
     _____      ________   _____    
    |_   _|    |  __   _| |_   _|   
      | |      |_/  / /     | |     
      | |   _     [<:] _    | |   _ 
     _| |__/ |  _/ /__/ |  _| |__/ |
    |________| |________| |________|
")

file(WRITE ${LZL_CPP_LIB_LOGO_FILE} "\
/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

#ifndef LZL_LOGO_HEADER
#define LZL_LOGO_HEADER

namespace lzl {

struct Logo
{
    static constexpr const char* value = R\"(${LZL_CPP_LIB_LOGO_VALUE}\n)\";
    static constexpr const char* name = \"lzl\";
};

} // namespace lzl

#endif // LZL_LOGO_HEADER
")

message(STATUS "Write logo header file to \"${LZL_CPP_LIB_LOGO_FILE}\".")
message(STATUS "Logo: ${LZL_CPP_LIB_LOGO_VALUE}.")

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
