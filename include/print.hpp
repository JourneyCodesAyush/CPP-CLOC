#pragma once
#include <vector>
#include <iostream>
#include <map>

#include "stats.hpp"
#include "detector.hpp"

namespace print
{
    void print_result_map(std::map<detector::FileType, stats::Stats> &statistics, double duration_ms);
    void print_single(stats::Stats &statistic);
}
