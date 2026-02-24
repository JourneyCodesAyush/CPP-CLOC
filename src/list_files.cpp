#include <vector>
#include <string>
#include <filesystem>
#include <exception>
#include <algorithm>
#include <unordered_set>

#include "list_files.hpp"

namespace fs = std::filesystem;

std::vector<std::string> list_files(const std::string &path, const std::unordered_set<std::string> &exclude_dir)
{

    std::vector<std::string> files;

    if (fs::is_directory(path))
    {
        try
        {
            for (auto entry = fs::recursive_directory_iterator(path);
                 entry != fs::recursive_directory_iterator();
                 ++entry)
            {
                if (entry->is_regular_file())
                {
                    files.push_back(entry->path().string());
                }
                else if (entry->is_directory())
                {
                    if (exclude_dir.count(entry->path().filename().string()) > 0)
                    {
                        entry.disable_recursion_pending();
                        continue;
                    }
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