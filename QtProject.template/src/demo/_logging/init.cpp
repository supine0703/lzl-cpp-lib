/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/
/*******************************************************************************
**
** License: MIT
** Copyright (c) 2016 - present, Gabi Melman and spdlog contributors.
** Repository: https://github.com/gabime/spdlog
**
*******************************************************************************/

#include "init.h"

#include "sinks/ansi_color_stdout_sink.h"
#include "sinks/daily_with_header_file_sink.h"

#include <QDateTime>

#include <spdlog/spdlog.h>

using namespace PROJ_NAMESPACE::sinks;

static constexpr std::string_view logger_name = FIXED_FLAG "/global_logger";

namespace PROJ_NAMESPACE::demo {

void initLogging()
{
    std::vector<spdlog::sink_ptr> sinks{};

    if constexpr (LOGGING_STDOUT_ENABLED)
    {
        // ⭐ stderr 彩色输出（Qt Creator 能识别 ANSI 颜色）
        sinks.push_back(std::make_shared<ansi_color_stdout_sink>());
    }

    if constexpr (LOGGING_FILE_ENABLED)
    {
        // ⭐ 文件日志（按日期滚动 + header）
        static constexpr std::string_view header_fmt =
            "\n=============================\n"
            "Segment Index: {}\n"
            "App: {}\n"
            "Version: {}\n"
            "Start Time: {}\n"
            "=============================\n";
        const auto start_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        sinks.push_back(
            std::make_shared<daily_with_header_file_sink>(LOGGING_FILE_DIR, [start_time](std::size_t segment_index) {
                return fmt::format(header_fmt, segment_index, APP_NAME, APP_VERSION, start_time);
            })
        );
    }

    // ⭐ 创建 logger
    {
        auto logger = std::make_shared<spdlog::logger>(std::string(logger_name), sinks.begin(), sinks.end());
        spdlog::set_default_logger(logger);
    }

    // ⭐ 设置日志等级
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);

    // ⭐ 程序启动时写入一次全局信息
    spdlog::info("===== Application Started =====");
    spdlog::info("App: " APP_NAME " " APP_VERSION);
    spdlog::info("Build: " BUILD_SYSTEM ", " BUILD_TIME);
    spdlog::info("================================");
}

} // namespace PROJ_NAMESPACE::demo
