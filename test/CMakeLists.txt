project(lzl-utils LANGUAGES CXX)

# It seems that MSVC explicitly specifies __cplusplus as 199711L
if(MSVC)
    add_definitions(-D__CPP_VERSION=_MSVC_LANG)
else()
    add_definitions(-D__CPP_VERSION=__cplusplus)
endif()

add_subdirectory(functional)
add_subdirectory(type)
