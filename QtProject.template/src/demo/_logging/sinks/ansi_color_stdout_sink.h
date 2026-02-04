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

#pragma once

#include <spdlog/details/os.h>
#include <spdlog/sinks/base_sink.h>

#include <chrono>
#include <mutex>

namespace PROJ_NAMESPACE::sinks {

// ===============================================
//   ANSI Color Formatter
//   - 格式化时间戳
//   - 彩色 level
//   - 正文
// ===============================================
class ansi_color_formatter : public spdlog::formatter
{
public:
    std::unique_ptr<spdlog::formatter> clone() const override { return std::make_unique<ansi_color_formatter>(); }

    void format(const spdlog::details::log_msg& msg, spdlog::memory_buf_t& dest) override
    {
        // -----------------------------
        // 1. 时间戳
        // -----------------------------

        // =======================================
        // 缓存秒级时间戳，毫秒每条日志追加
        // =======================================

        // 计算当前秒
        const auto duration = msg.time.time_since_epoch();
        const auto secs = std::chrono::duration_cast<std::chrono::seconds>(duration);

        // 如果秒变了 → 重新生成日期时间前缀
        if (cache_timestamp_ != secs || cached_datetime_.size() == 0)
        {
            cache_timestamp_ = secs;
            cached_datetime_.clear();

            const auto tt = spdlog::log_clock::to_time_t(msg.time);
            const auto tm = spdlog::details::os::localtime(tt);

            // 使用 fmt::format_to 写入缓存
            fmt::format_to(
                std::back_inserter(cached_datetime_),
                "[{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}.",
                tm.tm_year + 1900,
                tm.tm_mon + 1,
                tm.tm_mday,
                tm.tm_hour,
                tm.tm_min,
                tm.tm_sec
            );
        }

        // 把缓存的前缀写入 dest
        dest.append(cached_datetime_.begin(), cached_datetime_.end());

        // 追加毫秒
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
        fmt::format_to(std::back_inserter(dest), "{:03d}] ", static_cast<int>(ms));


        // -----------------------------
        // 2. 彩色 level
        // -----------------------------
        fmt::format_to(
            std::back_inserter(dest),
            "{}[{}]{} ",
            level_color(msg.level),
            spdlog::level::to_string_view(msg.level),
            RESET_TO_DEFAULT
        );

        // -----------------------------
        // 3. 正文
        // -----------------------------
        fmt::format_to(std::back_inserter(dest), "{}", msg.payload);
    }

private:
    // ANSI 颜色常量
    static constexpr std::string_view DEBUG_COLOR = "\033[36m";
    static constexpr std::string_view INFO_COLOR = "\033[32m";
    static constexpr std::string_view WARN_COLOR = "\033[33m";
    static constexpr std::string_view ERROR_COLOR = "\033[31m";
    static constexpr std::string_view CRITICAL_COLOR = "\033[41;37m";
    static constexpr std::string_view RESET_TO_DEFAULT = "\033[0m\033[39m";

    const std::string_view& level_color(spdlog::level::level_enum lvl) const noexcept
    {
        switch (lvl)
        {
        case spdlog::level::debug:
            return DEBUG_COLOR;
        case spdlog::level::info:
            return INFO_COLOR;
        case spdlog::level::warn:
            return WARN_COLOR;
        case spdlog::level::err:
            return ERROR_COLOR;
        case spdlog::level::critical:
            return CRITICAL_COLOR;
        default:
            return RESET_TO_DEFAULT;
        }
    }

    std::chrono::seconds cache_timestamp_{0};
    spdlog::memory_buf_t cached_datetime_;
};


// ===============================================
//   ANSI Color Stdout Sink
//   - 使用 ansi_color_formatter
//   - 输出到 stdout
//   - 自动加锁（base_sink）
// ===============================================
class ansi_color_stdout_sink : public spdlog::sinks::base_sink<std::mutex>
{
public:
    ansi_color_stdout_sink() : base_sink(std::make_unique<ansi_color_formatter>()) {}

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);

        std::fwrite(formatted.data(), 1, formatted.size(), stdout);
        std::fputc('\n', stdout);
        std::fflush(stdout);
    }

    void flush_() override { std::fflush(stdout); }
};

} // namespace PROJ_NAMESPACE::sinks
