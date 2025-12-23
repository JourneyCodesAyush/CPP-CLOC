#include <vector>
#include <iostream>
#include <iomanip>

#include "print.hpp"
#include "stats.hpp"

static void print_dashes()
{
    std::cout << "------------------------------------------------------------------------------";
}

void print::print_single(stats::Stats &stats)
{
    std::cout << std::left << std::setw(20) << stats.file_type
              << std::right << std::setw(8) << stats.file_count
              << std::setw(9) << stats.lines_of_code
              << std::setw(12) << stats.lines_of_comment
              << std::setw(13) << stats.blank_lines
              << std::setw(15) << stats.total()
              << "\n";
}

void print::print_result_map(std::map<detector::FileType, stats::Stats> &statistics, double duration_ms)
{
    std::cout << "\n\nC++ implementation of CLOC\n";
    std::cout << "Total time: " << duration_ms << " seconds\n";
    print_dashes();
    std::cout << "\n";
    // Header
    std::cout << std::left << std::setw(20) << "Language"
              << std::right << std::setw(8) << "Files"
              << std::setw(9) << "Code"
              << std::setw(12) << "Comments"
              << std::setw(13) << "Blank"
              << std::setw(15) << "Total"
              << "\n";

    stats::Stats total_stats;
    total_stats.file_type = "SUM"; // For the last row

    for (auto &pair : statistics)
    {
        print_dashes();
        std::cout << "\n";
        print_single(pair.second);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }

    print_dashes();
    std::cout << "\n";
    print_single(total_stats);
    print_dashes();
    std::cout << "\n";
}
