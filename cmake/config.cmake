# License: MIT
# Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
# Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# It seems that MSVC explicitly specifies __cplusplus as 199711L
if(MSVC)
    add_definitions(-D__CPP_VERSION=_MSVC_LANG)
else()
    add_definitions(-D__CPP_VERSION=__cplusplus)
endif()

# 设置编译选项，为了在Windows下能够正确显示中文
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /source-charset:utf-8 /execution-charset:GBK")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    string(APPEND CMAKE_CXX_FLAGS " -fexec-charset=GBK")
endif()
