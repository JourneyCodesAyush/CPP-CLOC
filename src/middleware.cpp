#include <vector>
#include <chrono>
#include <map>
#include <string>

#include "middleware.hpp"
#include "detector.hpp"
#include "stats.hpp"
#include "result.hpp"
#include "print.hpp"
#include "analyzer.hpp"
#include "comment_syntax.hpp"

struct ChunkResult
{
    std::map<detector::FileType, stats::Stats> stats;
    int ignored;
};

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

static stats::Stats analyze_and_merge(const std::string &filename, const comment_syntax::CommentSyntax &syntax, const std::string &file_extension)
{
    stats::Stats new_stats = analyzer::analyze_files(filename, syntax);
    new_stats.file_type = file_extension;
    return new_stats;
}

static std::vector<std::vector<std::string>> split_into_chunks(const std::vector<std::string> &files, size_t chunks)
{
    if (chunks == 0)
        return {files};

    const int number_of_files = files.size();

    if (number_of_files == 0)
        return {};

    const int chunk_size = number_of_files / chunks;

    std::vector<std::vector<std::string>> file_chunks;

    for (size_t i = 0; i < chunks; i++)
    {
        int start = i * chunk_size;

        int end;
        if (i == chunks - 1)
            end = number_of_files;
        else
            end = start + chunk_size;

        file_chunks.push_back(std::vector<std::string>(files.begin() + start, files.begin() + end));
    }
    return file_chunks;
}

static ChunkResult process_singles(const std::vector<std::string> &files)
{
    std::map<detector::FileType, stats::Stats> statistics_map;
    int ignored_files = 0;

    for (const std::string &filename : files)
    {
        detector::FileType file_type = detector::detect_file_type(filename);
        switch (file_type)
        {
        case detector::FileType::ASSEMBLY:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::AssemblyComments, "Assembly");
            check_and_merge(statistics_map, new_stat, file_type);

            break;
        }
        case detector::FileType::C:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "C");
            check_and_merge(statistics_map, new_stat, file_type);

            break;
        }
        case detector::FileType::CPP:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "C++");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::C_CPP_HEADER:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "C/C++ Header");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::JAVA:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "Java");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }

        case detector::FileType::PYTHON:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::PythonComments, "Python");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::HTML:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::HTMLMarkdownComments, "HTML");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::MARKDOWN:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::HTMLMarkdownComments, "MarkDown");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::CSS:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CssSyntax, "CSS");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::JAVASCRIPT:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "JavaScript");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::TYPESCRIPT:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "TypeScript");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::JSON:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::CLikeComments, "JSON");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::BASH:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::BashYMLComments, "Bash");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }
        case detector::FileType::POWERSHELL:
        {
            auto new_stat = analyze_and_merge(filename, comment_syntax::PowerShellComments, "PowerShell");
            check_and_merge(statistics_map, new_stat, file_type);
            break;
        }

        case detector::FileType::BATCH:
            // TODO: Comment syntax is '@REM' and '::'
            break;

        case detector::FileType::UNKNOWN:
            ignored_files++;
            break;
        default:
            ignored_files++;
            break;
        }
    }

    return ChunkResult{statistics_map, ignored_files};
}

result::Result middleware::process_file(const std::vector<std::string> &files)
{
    std::map<detector::FileType, stats::Stats> statistics_map;
    int total_files = files.size();
    int ignored_files = 0;

    auto start = std::chrono::high_resolution_clock::now();

    if (files.empty())
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        return result::Result{statistics_map, duration_ms, 0, 0};
    }

    ChunkResult chunk_result = process_singles(files);

    statistics_map = chunk_result.stats;
    ignored_files = chunk_result.ignored;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // double duration_seconds = duration_ms / 1000.0;

    return result::Result{statistics_map, duration_ms, total_files, ignored_files};
}
