project(${PARENT_PROJECT_PREFIX}_demo VERSION 0.1.0 LANGUAGES CXX)

# Set version suffix
set(PROJECT_VERSION_SUFFIX ".beta")

# For Qt-Designer can find UI files (Qt6 maybe not need this)
# list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS
# ... ...
# )

# Include current source directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(RESOURCES_FILES
    _res/_.qrc
    _res/app_ico.rc
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
    _logging/sinks/ansi_color_stdout_sink.h
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
    APP_VERSION="${PROJECT_VERSION}${PROJECT_VERSION_SUFFIX}"
    APP_NAME="${PARENT_APP_NAME_PREFIX} Demo"
    ORG_NAME=""
    DEV_TEAM_MEMBER="李宗霖"

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
    LOGGING_FILE_DIR=".logs/${PROJECT_NAME}$-{PROJECT_VERSION}${PROJECT_VERSION_SUFFIX}"
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
