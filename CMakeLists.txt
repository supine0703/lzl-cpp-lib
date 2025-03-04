# License: MIT
# Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
# Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>

cmake_minimum_required(VERSION 3.16)

project(lzl-cpp-lib VERSION 0.2.1 LANGUAGES CXX)

# Set the cmake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import the relevant cmake configuration
include(compiler_settings)
include(copy_lib_interface_headers)
include(copy_dirs_if_diff)
include(auto_install_post_build)
include(GNUInstallDirs)

# Include headers directory which copy_lib_interface_headers output
include_directories(${LIB_INTERFACE_HEADERS_INCLUDEDIR})

# qt auto settings
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

# Add the subdirectory
add_subdirectory(logo)
add_subdirectory(utils)
add_subdirectory(test)
