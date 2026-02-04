# ================================
# spdlog 配置
# ================================
set(SPDLOG_INSTALL ON)

# set(SPDLOG_BUILD_SHARED ON)

# ================================
# 添加 spdlog 子目录
# ===============================
add_subdirectory(spdlog)

# ================================
# 安装选项
# ================================
if(TARGET spdlog::spdlog)
    add_auto_install_post_build_not_custom_if_enable(spdlog::spdlog spdlog)
endif()
