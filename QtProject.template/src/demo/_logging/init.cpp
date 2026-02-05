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

#include "sinks/daily_with_header_file_sink.h"

#include <QDateTime>

#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/spdlog.h>

#if defined(_WIN32) && !defined(SPDLOG_HEADER_ONLY)
    #include <spdlog/sinks/ansicolor_sink-inl.h>
#endif

// clang-format off
#define HEADER_FMT                                        \
    SPDLOG_EOL "=============================" SPDLOG_EOL \
    "Segment Index: {}" SPDLOG_EOL                        \
    "App: " APP_NAME SPDLOG_EOL                           \
    "Version: " APP_VERSION SPDLOG_EOL                    \
    "Build: " BUILD_SYSTEM ", " BUILD_TIME SPDLOG_EOL     \
    "Start Time: {}" SPDLOG_EOL                           \
    "=============================" SPDLOG_EOL
// clang-format on

using namespace PROJ_NAMESPACE::sinks;

namespace {
static constexpr std::string_view logger_name = FIXED_FLAG "/global_logger";
[[nodiscard]] inline bool isRunningInQtCreator() noexcept
{
    static constexpr const char* qtcreator_run_env_var = "QTC_RUN";
    return ::qEnvironmentVariableIsSet(qtcreator_run_env_var);
}
} // namespace

namespace PROJ_NAMESPACE::demo {

void initLogging()
{
    std::vector<spdlog::sink_ptr> sinks{};

    if constexpr (LOGGING_STDOUT_ENABLED)
    {
        // ⭐ stdout 彩色输出（Qt Creator 能识别 ANSI 颜色）
        if (isRunningInQtCreator())
        {
            const auto stdout_sink =
                std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>(spdlog::color_mode::always);
            sinks.push_back(stdout_sink);
        }
    }

    if constexpr (LOGGING_FILE_ENABLED)
    {
        // ⭐ 文件日志（按日期滚动 + header）
        static constexpr std::string_view header_fmt = HEADER_FMT;
        const auto start_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        const auto file_sink =
            std::make_shared<daily_with_header_file_sink_mt>(LOGGING_FILE_DIR, [start_time](std::size_t segment_i) {
                return fmt::format(header_fmt, segment_i, start_time);
            });
        sinks.push_back(file_sink);
    }

    // ⭐ 创建 logger
    {
        auto logger = std::make_shared<spdlog::logger>(std::string(logger_name), sinks.begin(), sinks.end());
        spdlog::set_default_logger(logger);
    }

    // ⭐ 设置日志格式和级别
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %^[%l]%$ %v");
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);

    // ⭐ 程序启动时写入一次全局信息
    spdlog::info("===== Application Started =====");
    spdlog::info("App: " APP_NAME " " APP_VERSION);
    spdlog::info("Build: " BUILD_SYSTEM ", " BUILD_TIME);
    spdlog::info("================================");
}

} // namespace PROJ_NAMESPACE::demo
