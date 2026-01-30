# Function to add a post build step to install the target
# Arguments:
# + TARGET - Name of the target to install (Required)
function(add_auto_install_post_build_if_enable TARGET)
    if(AUTO_INSTALL_POST_BUILD)
        add_custom_command(
            TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()
endfunction()

# Function to add a custom target to install the target directory
# Arguments:
# + TARGET - Name of the target to install (Required)
# + TARGET_DIR - Directory of the target to install (Required)
function(add_auto_install_post_build_not_custom_if_enable TARGET TARGET_DIR)
    if(AUTO_INSTALL_POST_BUILD)
        add_custom_target(${TARGET}_post_build_install ALL
            COMMAND ${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DIR}
        )
        add_dependencies(${TARGET}_post_build_install ${TARGET})
    endif()
endfunction()
