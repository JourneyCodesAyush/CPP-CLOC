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

        Result(std::map<detector::FileType, stats::Stats> statistics, std::chrono::milliseconds time_elapsed)
        {
            this->statistics = statistics;
            this->time_elapsed = time_elapsed;
        }
    };

}