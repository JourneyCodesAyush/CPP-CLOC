#include <vector>
#include <string>
#include <filesystem>
#include <exception>

#include "list_files.hpp"

std::vector<std::string> list_files(const std::string &path)
{
    namespace fs = std::filesystem;

    std::vector<std::string> files;

    if (fs::is_directory(path))
    {
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
            throw std::runtime_error(std::string("Error processing files...\n %s") + e.what());
        }
    }
    else if (fs::is_regular_file(path))
    {
        files.push_back(fs::path(path).string());
    }
    return files;
}