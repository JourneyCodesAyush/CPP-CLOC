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
