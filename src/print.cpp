#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "print.hpp"
#include "stats.hpp"
#include "result.hpp"

static void print_single_json(const stats::Stats &stat, std::stringstream &output);
static void print_json(const result::Result &res, std::stringstream &output);

static void print_single_csv(const stats::Stats &stat, std::stringstream &output);
static void print_csv(const result::Result &res, std::stringstream &output);

static void print_single_xml(const stats::Stats &stat, std::stringstream &output);
static void print_xml(const result::Result &res, std::stringstream &output);

static void print_dashes(std::stringstream &output)
{
    output << "--------------------------------------------------------------------------------------";
}

static void print_single(const stats::Stats &stats, std::stringstream &output)
{
    output << std::left << std::setw(20) << stats.file_type
           << std::right << std::setw(8) << stats.file_count
           << std::setw(15) << stats.lines_of_code
           << std::setw(13) << stats.lines_of_comment
           << std::setw(13) << stats.blank_lines
           << std::setw(17) << stats.total()
           << "\n";
}

static void print_stdout(const result::Result &res, std::stringstream &output)
{
    output << "       " << res.total_files << " total files.\n";
    output << "       " << (res.total_files - res.ignored_files) << " files analyzed.\n";
    output << "       " << res.ignored_files << " files ignored.\n";
    output << "\nC++ implementation of CLOC\n";
    output << print::info.repo_link << "\t" << print::info.latest_tag << "\tTotal time: " << std::fixed << std::setprecision(4) << res.time_elapsed.count() / 1000.0 << " seconds\n";
    print_dashes(output);
    output << "\n";
    // Header
    output << std::left << std::setw(20) << "Language"
           << std::right << std::setw(8) << "Files"
           << std::setw(15) << "Code"
           << std::setw(13) << "Comments"
           << std::setw(13) << "Blank"
           << std::setw(17) << "Total"
           << "\n";

    stats::Stats total_stats;
    total_stats.file_type = "SUM"; // For the last row

    for (const auto &pair : res.statistics)
    {
        print_dashes(output);
        output << "\n";
        print_single(pair.second, output);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }

    print_dashes(output);
    output << "\n";
    print_single(total_stats, output);
    print_dashes(output);
    output << "\n";
}

std::string print::print_result_map(const result::Result &res, const print::OutputFormat format)
{
    std::stringstream output;
    switch (format)
    {
    case print::OutputFormat::STDOUT:
        print_stdout(res, output);
        break;
    case print::OutputFormat::JSON:
        print_json(res, output);
        break;
    case print::OutputFormat::CSV:
        print_csv(res, output);
        break;
    case print::OutputFormat::XML:
        print_xml(res, output);
        break;
    default:
        break;
    }

    return output.str();
}

static void print_single_json(const stats::Stats &stat, std::stringstream &output)
{
    output
        << "\"" << stat.file_type << "\" :{\n"
        << "  \"nFiles\": " << stat.file_count << ",\n"
        << "  \"blank\": " << stat.blank_lines << ",\n"
        << "  \"comment\": " << stat.lines_of_comment << ",\n"
        << "  \"code\": " << stat.lines_of_code << "\n"
        << "}";
}

static void print_json(const result::Result &res, std::stringstream &output)
{
    output << "{";

    // Header
    output << "\"header\" : {\n"
           << "  \"cpp_cloc_url\"    : \"" << print::info.repo_link << "\",\n"
           << "  \"cpp_cloc_tag\"    : \"" << print::info.latest_tag << "\",\n"
           << "  \"elapsed_seconds\" : "
           << std::fixed << std::setprecision(6)
           << res.time_elapsed.count() / 1000.0 << ",\n"
           << "  \"files_per_second\": "
           << std::fixed << std::setprecision(13) << (res.total_files - res.ignored_files) / (res.time_elapsed.count() / 1000.0)
           << "\n"
           << "},\n";

    stats::Stats total_stats;
    total_stats.file_type = "SUM";

    bool first = true;
    for (const auto &pair : res.statistics)
    {
        if (!first)
        {
            output << ",\n";
        }
        first = false;

        print_single_json(pair.second, output);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }

    // SUM (always last)
    output << ",\n";
    print_single_json(total_stats, output);

    output << "}";
}

static void print_single_csv(const stats::Stats &stat, std::stringstream &output)
{
    output << stat.file_count << ","
           << stat.file_type << ","
           << stat.blank_lines << ","
           << stat.lines_of_comment << ","
           << stat.lines_of_code << ""
           << "\n";
}
static void print_csv(const result::Result &res, std::stringstream &output)
{
    output << "files,language,blank,comment,code, \"" << print::info.repo_link << " "
           << print::info.latest_tag << " Elapsed seconds="
           << std::fixed << std::setprecision(6)
           << res.time_elapsed.count() / 1000.0 << " ("
           << std::fixed << std::setprecision(2) << (res.total_files - res.ignored_files) / (res.time_elapsed.count() / 1000.0)
           << " files/s)\""
           << "\n";

    stats::Stats total_stats;
    total_stats.file_type = "SUM";

    for (const auto &pair : res.statistics)
    {
        print_single_csv(pair.second, output);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }
    print_single_csv(total_stats, output);
}

static void print_single_xml(const stats::Stats &stat, std::stringstream &output)
{
    output << "  <language name=\"" << stat.file_type
           << "\" files_count=\"" << stat.file_count
           << "\" blank=\"" << stat.blank_lines
           << "\" comment=\"" << stat.lines_of_comment
           << "\" code=\"" << stat.lines_of_code << "\" />\n";
}

static void print_xml(const result::Result &res, std::stringstream &output)
{
    output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><results>\n"
           << "<header>\n"
           << "  <cpp_cloc_url>" << print::info.repo_link << "</cpp_cloc_url>\n"
           << "  <cpp_cloc_tag>" << print::info.latest_tag << "</cpp_cloc_tag>\n"
           << "  <elapsed_seconds>" << std::fixed << std::setprecision(11)
           << res.time_elapsed.count() / 1000.0 << "</elapsed_seconds>\n"
           << "  <n_files>" << (res.total_files - res.ignored_files) << "</n_files>\n"
           << "  <files_per_second>"
           << std::fixed << std::setprecision(13) << (res.total_files - res.ignored_files) / (res.time_elapsed.count() / 1000.0) << "</files_per_second>\n"
           << "</header>\n";
    output << "<languages>\n";
    stats::Stats total_stats;
    total_stats.file_type = "SUM";

    for (const auto &pair : res.statistics)
    {
        print_single_xml(pair.second, output);

        total_stats.lines_of_code += pair.second.lines_of_code;
        total_stats.lines_of_comment += pair.second.lines_of_comment;
        total_stats.blank_lines += pair.second.blank_lines;
        total_stats.file_count += pair.second.file_count;
    }

    output << "  <total sum_files=\"" << total_stats.file_count
           << "\" blank=\"" << total_stats.blank_lines
           << "\" comment=\"" << total_stats.lines_of_comment
           << "\" code=\"" << total_stats.lines_of_code << "\" />\n";

    output << "</languages>\n"
           << "</results>\n";
}
