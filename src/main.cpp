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

#include "list_files.hpp"
#include "middleware.hpp"
#include "print.hpp"

int main(int argc, char const *argv[])
{
    argparse::ArgumentParser program("cpp_cloc", print::info.latest_tag.data());

    program.add_argument("path").help("File or directory to analyze");

    // program.format_usage("Usage: cpp_cloc path [--help] [--version] [[--json]|[--csv]|[--xml]] ");
    program.add_description("Count physical lines of C++ source code in files or directories, recursively. Outputs results to console, JSON, CSV, or XML.");

    auto &group = program.add_mutually_exclusive_group();

    group.add_argument("--json").help("Write the results as JavaScript Object Notation (JSON) formatted output.").flag();
    group.add_argument("--csv").help("Write the results as comma separated values").flag();
    group.add_argument("--xml").help("Write the results in XML").flag();

    try
    {
        program.parse_args(argc, argv);

        std::string path = program.get<std::string>("path");
        auto files = list_files(path);
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
        print::print_result_map(res, output);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
