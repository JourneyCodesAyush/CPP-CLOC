#include <vector>
#include <string>
#include <filesystem>
#include <exception>

#include "list_files.hpp"

std::vector<std::string> list_files(const std::string &path)
{
    namespace fs = std::filesystem;
    std::vector<std::string> files;
    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path().string());
            }
        }
    }
    catch (std::exception &e)
    {
    }
    return files;
}