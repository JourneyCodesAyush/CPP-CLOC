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

int main(int argc, char const *argv[])
{
    argparse::ArgumentParser program("cpp_cloc");

    program.add_argument("path").help("File or directory to analyze");

    try
    {
        program.parse_args(argc, argv);

        std::string path = program.get<std::string>("path");
        auto files = list_files(path);
        middleware::process_file(files);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
