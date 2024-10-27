# License: MIT
# Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
# Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>

cmake_minimum_required(VERSION 3.15)

project(lzl-cpp-lib VERSION 0.1.1 LANGUAGES CXX)

include(logo/logo.cmake)
include(cmake/config.cmake)

include_directories(type)
include_directories(functional)

add_subdirectory(type)
add_subdirectory(functional)
