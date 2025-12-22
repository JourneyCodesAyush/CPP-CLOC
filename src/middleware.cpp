#include <vector>
#include <chrono>
#include <map>

#include "middleware.hpp"
#include "detector.hpp"
#include "stats.hpp"
#include "print.hpp"
#include "analyzer.hpp"
#include "comment_syntax.hpp"

static void check_and_merge(std::map<detector::FileType, stats::Stats> &statistics_map, stats::Stats &new_stats, const detector::FileType &file_type)
{
    if (statistics_map.count(file_type))
    {
        statistics_map[file_type].merge(new_stats);
    }
    else
    {
        statistics_map[file_type] = new_stats;
    }
}

void middleware::process_file(const char *filename)
{
    std::map<detector::FileType, stats::Stats> statistics_map;

    auto start = std::chrono::high_resolution_clock::now();

    detector::FileType file_type = detector::detect_file_type(filename);
    switch (file_type)
    {
    case detector::FileType::C:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);
        new_stats.file_type = "C";
        check_and_merge(statistics_map, new_stats, file_type);

        break;
    }
    case detector::FileType::CPP:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);
        new_stats.file_type = "C++";
        check_and_merge(statistics_map, new_stats, file_type);

        break;
    }
    case detector::FileType::JAVA:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);
        new_stats.file_type = "Java";
        check_and_merge(statistics_map, new_stats, file_type);

        break;
    }

    case detector::FileType::PYTHON:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::PythonComments);
        new_stats.file_type = "Python";
        check_and_merge(statistics_map, new_stats, file_type);
        break;
    }
    case detector::FileType::BASH:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::BashPowerShellComments);
        new_stats.file_type = "Bash";
        check_and_merge(statistics_map, new_stats, file_type);
        break;
    }
    case detector::FileType::POWERSHELL:
    {
        stats::Stats new_stats = analyzer::analyze_files(filename, comment_syntax::BashPowerShellComments);
        new_stats.file_type = "PowerShell";
        check_and_merge(statistics_map, new_stats, file_type);
        break;
    }

    case detector::FileType::BATCH:
        // TODO: Comment syntax is '@REM' and '::'
        break;

    case detector::FileType::UNKNOWN:
        break;
    default:
        break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    double duration_seconds = duration_ms / 1000.0;

    print::print_result_map(statistics_map, duration_seconds);
}