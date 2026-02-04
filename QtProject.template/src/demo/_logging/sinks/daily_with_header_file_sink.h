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

#include <fstream>
#include <mutex>

namespace PROJ_NAMESPACE::sinks {

class daily_with_header_file_sink : public spdlog::sinks::base_sink<std::mutex>
{
public:
    using header_generator_t = std::function<std::string(std::size_t segment_index)>;

    explicit daily_with_header_file_sink(const std::string& base_path, header_generator_t header_generator)
        : base_sink(), base_path_(base_path), header_generator_(std::move(header_generator))
    {
        open_new_file();
        write_header();
    }

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        const auto today = current_date_string();
        if (today != current_date_)
        {
            segment_index_++;
            open_new_file();
            write_header();
        }

        file_stream_ << fmt::to_string(msg.payload) << "\n";
        file_stream_.flush();
    }

    void flush_() override { file_stream_.flush(); }

private:
    std::string base_path_;
    std::ofstream file_stream_;
    std::string current_date_;
    header_generator_t header_generator_;
    std::size_t segment_index_ = 1;

    std::string current_date_string()
    {
        const auto tm = spdlog::details::os::localtime();
        return fmt::format("{:04d}-{:02d}-{:02d}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    }

    void open_new_file()
    {
        current_date_ = current_date_string();
        const auto filename = fmt::format("{}/{}.log", base_path_, current_date_);

        file_stream_.close();
        file_stream_.open(filename, std::ios::app);
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
};

} // namespace PROJ_NAMESPACE::sinks
