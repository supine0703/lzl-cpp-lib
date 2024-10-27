# License: MIT
# Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
# Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>

set(LZL_CPP_LIB_LOGO_PATH ${CMAKE_SOURCE_DIR}/logo)
set(LZL_CPP_LIB_LOGO_FILE ${LZL_CPP_LIB_LOGO_PATH}/lzl_logo.h)
set(LZL_CPP_LIB_LOGO_VALUE "
     _____      ________   _____    
    |_   _|    |  __   _| |_   _|   
      | |      |_/  / /     | |     
      | |   _     [<:] _    | |   _ 
     _| |__/ |  _/ /__/ |  _| |__/ |
    |________| |________| |________|
")

file(WRITE ${LZL_CPP_LIB_LOGO_FILE} "\
/**
 * License: MIT
 * Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#ifndef LZL_LOGO_H
#define LZL_LOGO_H

namespace lzl {

struct Logo
{
    static constexpr const char* value = R\"(${LZL_CPP_LIB_LOGO_VALUE}\n)\";
    static constexpr const char* name = \"lzl\";
};

} // namespace lzl

#endif // LZL_LOGO_H
")

message(STATUS "Write logo header file to \"${LZL_CPP_LIB_LOGO_FILE}\".")

message(STATUS "Logo: ${LZL_CPP_LIB_LOGO_VALUE}.")

include_directories(${LZL_CPP_LIB_LOGO_PATH})
message(STATUS "Include logo header file path: \"${LZL_CPP_LIB_LOGO_PATH}\".")
