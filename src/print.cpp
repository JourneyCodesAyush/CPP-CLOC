#include <vector>
#include <iostream>
#include <iomanip>

#include "print.hpp"
#include "stats.hpp"

void print::print_single(stats::Stats &stats)
{
    std::cout << std::left << std::setw(12) << stats.file_type
              << std::right << std::setw(6) << stats.file_count
              << " | " << std::setw(6) << stats.lines_of_code
              << " | " << std::setw(8) << stats.lines_of_comment
              << " | " << std::setw(12) << stats.blank_lines
              << " | " << std::setw(11) << stats.total()
              << "\n";
}

void print::print_result_map(std::map<detector::FileType, stats::Stats> &statistics)
{
    std::cout << "C++ implementation of CLOC\n";
    // Header
    std::cout << std::left << std::setw(12) << "Language"
              << std::right << std::setw(6) << "Files"
              << " | " << std::setw(6) << "Code"
              << " | " << std::setw(8) << "Comments"
              << " | " << std::setw(12) << "Blank lines"
              << " | " << std::setw(11) << "Total lines"
              << "\n";

    for (auto &pair : statistics)
    {
        print::print_single(pair.second);
    }
}
