# find Qt-bin path
find_program(QT_QMAKE_EXECUTABLE qmake HINTS ENV PATH)

if(NOT QT_QMAKE_EXECUTABLE)
    message(FATAL_ERROR "qmake not found. Please make sure Qt is installed and qmake is available in the PATH.")
endif()

get_filename_component(QT_QMAKE_DIR ${QT_QMAKE_EXECUTABLE} DIRECTORY)

message(STATUS "QT_QMAKE_DIR: ${QT_QMAKE_DIR}")

# Function to add a post build step to deploy the target for Windows
# Arguments:
# + TARGET_NAME - Name of the target to deploy (Required)
# + TARGET_PATH - Path to the target file to deploy (Optional)
function(add_auto_deploy_for_win_if_enable TARGET_NAME)
    set(non_value_args)
    set(one_value_args TARGET_PATH)
    set(multi_value_args)
    cmake_parse_arguments(ARG "${non_value_args}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    set(TARGET_PATH ${ARG_TARGET_PATH})

    if(AUTO_DEPLOY_FOR_WINDOWS)
        # check windeployqt
        find_program(WINDEPLOYQT_EXE windeployqt HINTS ${QT_QMAKE_DIR})

        if(NOT WINDEPLOYQT_EXE)
            message(FATAL_ERROR
                "windeployqt not found."
                "Please make sure Qt is installed and windeployqt is available."
            )
        endif()

        if(NOT TARGET_PATH)
            set(TARGET_PATH "$<TARGET_FILE:${TARGET_NAME}>")
        endif()

        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND echo "Running: ${WINDEPLOYQT_EXE} ${TARGET_PATH}"
            COMMAND ${WINDEPLOYQT_EXE} ${TARGET_PATH}
            COMMAND echo "Command End."
        )
    endif()
endfunction()
