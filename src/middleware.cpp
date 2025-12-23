#include <vector>
#include <chrono>
#include <map>
#include <string>

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

static void analyze_and_merge(std::map<detector::FileType, stats::Stats> &statistics_map, const std::string &filename, const comment_syntax::CommentSyntax &syntax, const detector::FileType &file_type, const std::string &file_extension)
{
    stats::Stats new_stats = analyzer::analyze_files(filename, syntax);
    new_stats.file_type = file_extension;
    check_and_merge(statistics_map, new_stats, file_type);
}

void middleware::process_file(const std::vector<std::string> &files)
{
    std::map<detector::FileType, stats::Stats> statistics_map;

    auto start = std::chrono::high_resolution_clock::now();

    for (const std::string &filename : files)
    {
        detector::FileType file_type = detector::detect_file_type(filename);
        switch (file_type)
        {
        case detector::FileType::C:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::CLikeComments, detector::FileType::C, "C");

            break;
        }
        case detector::FileType::CPP:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::CLikeComments, detector::FileType::CPP, "C++");
            break;
        }
        case detector::FileType::C_CPP_HEADER:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::CLikeComments, detector::FileType::CPP, "C/C++ Header");
            break;
        }
        case detector::FileType::JAVA:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::CLikeComments, detector::FileType::JAVA, "Java");
            break;
        }

        case detector::FileType::PYTHON:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::PythonComments, detector::FileType::C, "Python");
            break;
        }
        case detector::FileType::BASH:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::BashPowerShellComments, detector::FileType::BASH, "Bash");
            break;
        }
        case detector::FileType::POWERSHELL:
        {
            analyze_and_merge(statistics_map, filename, comment_syntax::BashPowerShellComments, detector::FileType::POWERSHELL, "PowerShell");
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
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    double duration_seconds = duration_ms / 1000.0;

    print::print_result_map(statistics_map, duration_seconds);
}
