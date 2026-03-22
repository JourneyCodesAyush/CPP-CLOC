// argparse.hpp
// -----------------------------
// This file is a header-only argument parser for C++.
// Original source: https://github.com/p-ranav/argparse
// License: MIT
//
// The file is included in CPP-CLOC to simplify setup.
// Please refer to the original repository for updates or full documentation.

#include <argparse/argparse.hpp>
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <unordered_set>

#include "list_files.hpp"
#include "middleware.hpp"
#include "print.hpp"
#include "string_operation_strip.hpp"

static std::unordered_set<std::string> parse_exclude_dirs(const std::string &str)
{
    auto forward_slash = str.find("/");
    auto back_slash = str.find("\\");
    if (forward_slash != std::string::npos || back_slash != std::string::npos)
    {
        throw std::invalid_argument(
            "--exclude-dir accepts directory names only (no '/' or '\\').\n"
            "Example: --exclude-dir=build,test");
    }

    std::unordered_set<std::string> result = {
        ".git",
        ".svn",
        ".hg",
        ".bzr",
        ".cvs",
        ".snapshot",
        "node_modules"};

    if (str.empty())
    {
        return result;
    }
    size_t start = 0;
    size_t end = str.find(',');
    while (end != std::string::npos)
    {
        result.insert(strip(str.substr(start, end - start)));
        start = end + 1;
        end = str.find(',', start);
    }
    result.insert(strip(str.substr(start)));
    return result;
}

int main(int argc, char const *argv[])
{
    // Disable sync with C stdio for slightly faster C++ stream I/O.
    // No measurable impact for file-heavy workloads, but safe here.
    std::ios::sync_with_stdio(false);

    argparse::ArgumentParser program("cpp_cloc", print::info.latest_tag.data());

    program.add_argument("path").help("File or directory to analyze");

    // program.format_usage("Usage: cpp_cloc path [--help] [--version] [[--json]|[--csv]|[--xml]] ");
    program.add_description("Count physical lines of source code in files or directories, recursively. Outputs results to console, JSON, CSV, or XML.");

    program.add_argument("--exclude-dir")
        .default_value("")
        .help("Exclude one or more directory names from recursive scanning\n"
              "Provide a comma-separated list (e.g. --exclude-dir=build,test)\n"
              "Matching is based on directory name only (not full path)");

    program.add_argument("--output")
        .default_value("")
        .help("Write output to a file instead of STDOUT");

    auto &group = program.add_mutually_exclusive_group();

    group.add_argument("--json").help("Write the results as JavaScript Object Notation (JSON) formatted output").flag();
    group.add_argument("--csv").help("Write the results as comma separated values").flag();
    group.add_argument("--xml").help("Write the results in XML").flag();

    try
    {
        program.parse_args(argc, argv);

        std::string path = program.get<std::string>("path");
        const std::string exclude_dir_string = program.get<std::string>("--exclude-dir");
        auto exclude_dir_set = parse_exclude_dirs(exclude_dir_string);

        auto files = list_files(path, exclude_dir_set);
        auto res = middleware::process_file(files);
        auto output = print::OutputFormat::STDOUT;

        if (program["--json"] == true)
        {
            output = print::OutputFormat::JSON;
        }
        else if (program["--csv"] == true)
        {
            output = print::OutputFormat::CSV;
        }
        else if (program["--xml"] == true)
        {
            output = print::OutputFormat::XML;
        }
        std::string string_output = print::print_result_map(res, output);

        const std::string output_file_name = program.get<std::string>("--output");
        if (!output_file_name.empty())
        {
            std::ofstream output_file(output_file_name);
            if (!output_file.is_open())
            {
                std::cerr << "Cannot open file: " << output_file_name << "\n";
                exit(EXIT_FAILURE);
            }

            output_file << string_output;
            if (output_file.fail())
            {
                std::cerr << "Failed to write to " << output_file_name << "\n";
                exit(EXIT_FAILURE);
            }
            std::cout << "Wrote " << output_file_name << "\n";
            output_file.flush();
            output_file.close();
        }
        else
        {
            std::cout << string_output;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred.\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}
