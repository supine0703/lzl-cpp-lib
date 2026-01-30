cmake_minimum_required(VERSION 3.19)

project(${PARENT_PROJECT_PREFIX}_libs)

# 设置父项目前缀
set(PARENT_PROJECT_PREFIX ${PARENT_PROJECT_PREFIX})

# 添加 utils_logger 库
add_subdirectory(utils_logger)
set(LIB_UTILS_LOGGER ${LIB_UTILS_LOGGER} PARENT_SCOPE)

# ... ... 添加其他库子目录

# Copy library interface headers
copy_lib_i_headers(VERBOSE
    HEADERS_FILES disable.h
)
