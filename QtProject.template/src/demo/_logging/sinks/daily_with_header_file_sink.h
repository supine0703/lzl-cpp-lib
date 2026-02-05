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

#include "spdlog/fmt/bundled/format.h"

#include <spdlog/details/os.h>
#include <spdlog/sinks/base_sink.h>

#include <fstream>
#include <functional>
#include <mutex>


namespace PROJ_NAMESPACE::sinks {

template <typename Mutex>
class daily_with_header_file_sink : public spdlog::sinks::base_sink<Mutex>
{
public:
    using header_generator_t = std::function<std::string(std::size_t segment_index)>;

    explicit daily_with_header_file_sink(const std::string& base_path, header_generator_t header_generator)
        : spdlog::sinks::base_sink<Mutex>(), base_path_(base_path), header_generator_(std::move(header_generator))
    {
        open_new_file();
        write_header();
    }

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        if (used_date_value_ != current_date_value())
        {
            segment_index_++;
            open_new_file();
            write_header();
        }

        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);

        file_stream_.write(formatted.data(), formatted.size());
        // file_stream_.flush(); // flush is handled in flush_(); spdlog::flush_on(...) will set when to call flush_
    }

    void flush_() override { file_stream_.flush(); }

private:
    const std::string base_path_;
    const header_generator_t header_generator_;
    std::ofstream file_stream_;
    std::size_t segment_index_ = 1;
    int used_date_value_ = 0;

    void open_new_file()
    {
        used_date_value_ = current_date_value();
        const auto filename = fmt::format("{}/{}.log", base_path_, format_date(used_date_value_));

        file_stream_.close();
        file_stream_.open(filename, std::ios::binary | std::ios::app);
        if (!file_stream_.is_open())
        {
            spdlog::throw_spdlog_ex(fmt::format("Failed to open log file: {}", filename));
        }
    }

    void write_header()
    {
        if (header_generator_)
        {
            file_stream_ << header_generator_(segment_index_);
            file_stream_.flush();
        }
    }

private:
    static int current_date_value() noexcept
    {
        const auto tm = spdlog::details::os::localtime();
        return (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
    }

    static std::string format_date(int date)
    {
        return fmt::format("{:04d}-{:02d}-{:02d}", date / 10000, (date / 100) % 100, date % 100);
    }
};

using daily_with_header_file_sink_mt = daily_with_header_file_sink<std::mutex>;
using daily_with_header_file_sink_st = daily_with_header_file_sink<spdlog::details::null_mutex>;

} // namespace PROJ_NAMESPACE::sinks
