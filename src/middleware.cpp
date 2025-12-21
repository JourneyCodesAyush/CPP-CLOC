#include <vector>
#include <iostream>
#include <map>

#include "middleware.hpp"
#include "detector.hpp"
#include "stats.hpp"
#include "print.hpp"
#include "analyzer_c_like.hpp"

void middleware::process_file(const char *filename)
{
    std::map<detector::FileType, stats::Stats> statistics_map;

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
        // TODO
        break;
    }
    case detector::FileType::JAVA:
    {
        // TODO
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

    print::print_result_map(statistics_map);
}