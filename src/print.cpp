#include <vector>
#include <iostream>
#include <iomanip>

#include "print.hpp"
#include "stats.hpp"
#include "result.hpp"

static void print_single_json(const stats::Stats &stat);
static void print_json(const result::Result &res);

static void print_dashes()
{
    std::cout << "------------------------------------------------------------------------------";
}

static void print_single(const stats::Stats &stats)
{
    std::cout << std::left << std::setw(20) << stats.file_type
              << std::right << std::setw(8) << stats.file_count
              << std::setw(9) << stats.lines_of_code
              << std::setw(12) << stats.lines_of_comment
              << std::setw(13) << stats.blank_lines
              << std::setw(15) << stats.total()
              << "\n";
}

static void print_stdout(const result::Result &res)
{
    std::cout << "\nC++ implementation of CLOC\n";
    std::cout << print::info.repo_link << "\t" << print::info.latest_tag << "\tTotal time: " << std::fixed << std::setprecision(4) << res.time_elapsed.count() / 1000.0 << " seconds\n";
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

    for (const auto &pair : res.statistics)
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

void print::print_result_map(const result::Result &res, const print::OutputFormat format)
{
    switch (format)
    {
    case print::OutputFormat::STDOUT:
        print_stdout(res);
        break;
    case print::OutputFormat::JSON:
        print_json(res);
        break;
    default:
        break;
    }
}

static void print_single_json(const stats::Stats &stat)
{
    std::cout
        << "\"" << stat.file_type << "\" :{\n"
        << "  \"nFiles\": " << stat.file_count << ",\n"
        << "  \"blank\": " << stat.blank_lines << ",\n"
        << "  \"comment\": " << stat.lines_of_comment << ",\n"
        << "  \"code\": " << stat.lines_of_code << "\n"
        << "}";
}

static void print_json(const result::Result &res)
{
    std::cout << "{";

    // Header
    std::cout << "\"header\" : {\n"
              << "  \"cloc_url\"        : \"" << print::info.repo_link << "\",\n"
              << "  \"cloc_version\"    : \"" << print::info.latest_tag << "\",\n"
              << "  \"elapsed_seconds\" : "
              << std::fixed << std::setprecision(6)
              << res.time_elapsed.count() / 1000.0 << "\n"
              << "},\n";

    stats::Stats total_stats;
    total_stats.file_type = "SUM";

    bool first = true;
    for (const auto &pair : res.statistics)
    {
        if (!first)
        {
            std::cout << ",\n";
        }
        first = false;

        print_single_json(pair.second);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }

    // SUM (always last)
    std::cout << ",\n";
    print_single_json(total_stats);

    std::cout << "}";
}
