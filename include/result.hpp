#pragma once

#include "stats.hpp"
#include "detector.hpp"
#include <map>
#include <chrono>

namespace result
{
    struct Result
    {
        std::map<detector::FileType, stats::Stats> statistics;
        std::chrono::milliseconds time_elapsed;
        int total_files;
        int ignored_files;

        Result(std::map<detector::FileType, stats::Stats> statistics, std::chrono::milliseconds time_elapsed, int total_files, int ignored_files)
        {
            this->statistics = statistics;
            this->time_elapsed = time_elapsed;
            this->total_files = total_files;
            this->ignored_files = ignored_files;
        }
    };

}