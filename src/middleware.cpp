#include <vector>
#include <chrono>
#include <map>

#include "middleware.hpp"
#include "detector.hpp"
#include "stats.hpp"
#include "print.hpp"
#include "analyzer_c_like.hpp"

void middleware::process_file(const char *filename)
{
    std::map<detector::FileType, stats::Stats> statistics_map;

    auto start = std::chrono::high_resolution_clock::now();

    detector::FileType file_type = detector::detect_file_type(filename);
    switch (file_type)
    {
    case detector::FileType::C:
    {
        stats::Stats new_stats = analyzer::analyze_c(filename);
        new_stats.file_type = "C";
        if (statistics_map.count(file_type))
        {
            statistics_map[file_type].merge(new_stats);
        }
        else
        {
            statistics_map[file_type] = new_stats;
        }
        break;
    }
    case detector::FileType::CPP:
    {
        stats::Stats new_stats = analyzer::analyze_c(filename);
        new_stats.file_type = "C++";
        if (statistics_map.count(file_type))
        {
            statistics_map[file_type].merge(new_stats);
        }
        else
        {
            statistics_map[file_type] = new_stats;
        }
        break;
    }
    case detector::FileType::JAVA:
    {
        stats::Stats new_stats = analyzer::analyze_c(filename);
        new_stats.file_type = "Java";
        if (statistics_map.count(file_type))
        {
            statistics_map[file_type].merge(new_stats);
        }
        else
        {
            statistics_map[file_type] = new_stats;
        }

        break;
    }

    case detector::FileType::PYTHON:
    {
        // TODO: Comment detection for Python
        // Must include triple quoted strings as comment
        break;
    }
    case detector::FileType::BASH:
    case detector::FileType::POWERSHELL:
        // TODO: '#' is the comment syntax
        // Similar syntax in Bash and PowerShell
        break;

    case detector::FileType::BATCH:
        // TODO: Comment syntax is '@REM' and '::'
        break;

    case detector::FileType::UNKNOWN:
        break;
    default:
        break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    double duration_seconds = duration_ms / 1000.0;

    print::print_result_map(statistics_map, duration_seconds);
}