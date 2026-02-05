# -----------------------------
# Version numbers (4 segments)
# -----------------------------
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# Version build
find_program(GIT_EXECUTABLE git)

if(GIT_EXECUTABLE)
    # Try to get commit count
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE VERSION_BUILD
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endif()

# Fallback if Git not found or not a repo
if(NOT VERSION_BUILD)
    set(VERSION_BUILD 0)
endif()

# -----------------------------
# Project definition
# -----------------------------
project(${PARENT_PROJECT_PREFIX}_demo
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    LANGUAGES CXX
)

# Set version suffix
set(PROJECT_VERSION_FULL "${PROJECT_VERSION}.beta")

# -----------------------------
# Icon file
# -----------------------------
set(APP_ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/_res/app_icon.ico")

# -----------------------------
# App info
# -----------------------------
set(FILE_DESCRIPTION "${PARENT_APP_NAME_PREFIX} Executable")
set(FILE_VERSION "${PROJECT_VERSION}.${VERSION_BUILD}")
set(PRODUCT_NAME "${PARENT_APP_NAME_PREFIX} Demo")
set(PRODUCT_VERSION "${PROJECT_VERSION_FULL}")
set(COMPANY_NAME "Lzl")
set(ORIGINAL_FILENAME "${PROJECT_NAME}")

# -----------------------------
# Generate version_info.rc
# -----------------------------
if(WIN32)
    set(RESOURCES_FILES
        ${CMAKE_BINARY_DIR}/version_info.rc
    )
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/_res/version_info.rc.in
        ${RESOURCES_FILES}
        @ONLY
    )
endif()

# -----------------------------
# Start Building Demo
# -----------------------------

# For Qt-Designer can find UI files (Qt6 maybe not need this)
# list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS
# ... ...
# )

# Include current source directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(RESOURCES_FILES
    ${RESOURCES_FILES}
    _res/_.qrc
)

set(OBJECT_SOURCES_FILES
    object/window_controller.cpp
    object/window_controller.h
)

set(DIALOG_SOURCES_FILES

    # dialog/...
)

set(WIDGET_SOURCES_FILES

    # widget/...
)

set(WINDOW_SOURCES_FILES

    # window/...
)

set(GLOBAL_SOURCES_FILES
    global.cpp
    global.h
    _logging/init.cpp
    _logging/init.h
    _logging/sinks/daily_with_header_file_sink.h
)

set(SOURCES_FILES
    main.cpp
    main_object.h
    ${OBJECT_SOURCES_FILES}
    ${DIALOG_SOURCES_FILES}
    ${WIDGET_SOURCES_FILES}
    ${WINDOW_SOURCES_FILES}
    ${GLOBAL_SOURCES_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${SOURCES_FILES}
        ${RESOURCES_FILES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${SOURCES_FILES}
        ${RESOURCES_FILES}
    )
endif()

# 定义宏
target_compile_definitions(${PROJECT_NAME} PRIVATE

    # Application information
    APP_VERSION="${PRODUCT_VERSION}"
    APP_NAME="${PRODUCT_NAME}"
    ORG_NAME="${COMPANY_NAME}"

    # Application flags
    FIXED_FLAG="lzl-demo"
    QRC_PREFIX=":/lzl/demo"

    # Build information
    BUILD_TIME="${CURRENT_TIME}"
    BUILD_SYSTEM="${SYSTEM_INFO}"
    BUILD_QT_VERSION="${QT_VERSION}"
    BUILD_C_COMPILER="${C_COMPILER_INFO}"
    BUILD_CXX_COMPILER="${CXX_COMPILER_INFO}"

    # Function switches
    SHOW_WATERMARK_ENABLED=1
    LOGGING_STDOUT_ENABLED=1
    LOGGING_FILE_ENABLED=1
    LOGGING_FILE_DIR=".logs/${PROJECT_NAME}[${PRODUCT_VERSION}].logs"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${LIB_UTILS_LOGGER}

    # spdlog::spdlog # if using spdlog directly
    # hidapi::hidapi # if using hidapi directly
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    WIN32_EXECUTABLE TRUE
)

# 安装 demo
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

# 添加自动安装和自动部署
add_auto_install_post_build_if_enable(${PROJECT_NAME})
add_auto_deploy_for_win_if_enable(${PROJECT_NAME}
    TARGET_PATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}.exe
)
