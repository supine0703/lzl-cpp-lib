# Append the cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Add lzl-qt-settings
# add_subdirectory(lzl-qt-settings)  # if use lzl-qt-settings lib

# Add hidapi for Windows
include(build_hidapi) # Only a template
