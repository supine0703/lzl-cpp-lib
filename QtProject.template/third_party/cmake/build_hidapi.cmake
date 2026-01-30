# This is just an example.
# If you need to view hidapi, you can visit: https://github.com/libusb/hidapi

# ================================
# 定义 hidapi 构建选项
# ================================
set(BUILD_SHARED_LIBS ${HIDAPI_USE_SHARED_LIBS})
set(HIDAPI_INSTALL_TARGETS ${INSTALL_HIDAPI_LIB})
set(HIDAPI_BUILD_HIDTEST FALSE)

if(WIN32)
    set(HIDAPI_WITH_TESTS FALSE)
endif()

# ================================
# 添加 hidapi 子目录
# ===============================
add_subdirectory(hidapi)

# ================================
# 安装选项
# ================================
if(TARGET hidapi::hidapi)
    add_auto_install_post_build_not_custom_if_enable(hidapi::hidapi hidapi)
endif()

# 清理变量
unset(BUILD_SHARED_LIBS)
unset(HIDAPI_BUILD_HIDTEST)
unset(HIDAPI_WITH_TESTS)
unset(HIDAPI_INSTALL_TARGETS)
