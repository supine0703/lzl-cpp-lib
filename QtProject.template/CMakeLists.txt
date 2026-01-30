cmake_minimum_required(VERSION 3.19)

project(qt-project-template)

# Options for installation and deployment
option(AUTO_INSTALL_POST_BUILD "Auto install after build" OFF)
option(AUTO_DEPLOY_FOR_WINDOWS "Auto deploy for windows" OFF)
option(INSTALL_LIBRARY_ARCHIVES "Install library archives" ON)
option(INSTALL_INTERFACE_HEADERS "Install interface headers" ON)

# option(INSTALL_LZL_QT_SETTINGS_LIB "Install lzl qt settings lib" ON)  # if use lzl-qt-settings lib

# Options for warnings and verbosity
option(WARN_ALL "Enable all warnings" ON)
option(COPY_DIRS_IF_DIFF_DISABLE_VERBOSE "Disable verbose output for copy_dirs_if_diff" ON)
option(COPY_LIB_INTERFACE_HEADERS_DISABLE_VERBOSE "Disable verbose output for copy_lib_interface_headers" ON)
option(GENERATE_EXPORTS_HEADER_DISABLE_VERBOSE "Disable verbose output for generate_lib_exports_header" ON)

# Check options consistency
if(AUTO_DEPLOY_FOR_WINDOWS)
    if(NOT WIN32)
        message(FATAL_ERROR "AUTO_DEPLOY_FOR_WINDOWS requires system to be Windows.")
    endif()

    if(NOT AUTO_INSTALL_POST_BUILD)
        message(FATAL_ERROR "AUTO_DEPLOY_FOR_WINDOWS requires AUTO_INSTALL_POST_BUILD to be ON.")
    endif()
endif()

# Append the cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import the relevant cmake configuration
include(compiler_settings)
include(copy_lib_interface_headers)
include(copy_dirs_if_diff)
include(auto_deploy_for_windows)
include(auto_install_post_build)
include(generate_lib_exports_header)

# Include headers directory which copy_lib_interface_headers output
include_directories(${LIB_INTERFACE_HEADERS_INCLUDEDIR})

# ==============================================================================

# Qt auto settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the Qt6 package
set(QT_COMPONENTS Core Widgets)
find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

# Add project definitions
add_compile_definitions(
    CONFIG_INI="config-${PROJECT_NAME}.ini"
    PROJ_NAMESPACE=lzl::qt::template
)

# Add third party
add_subdirectory(third_party) # if you have third party libraries

# Set parent project prefix
set(PARENT_PROJECT_PREFIX "lzl_qt_template")
set(PARENT_APP_NAME_PREFIX "LZL QT TEMPLATE")

# Add src
add_subdirectory(src)
