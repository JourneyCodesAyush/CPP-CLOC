#include <string>
#include <cctype>
#include <algorithm>
#include <filesystem>

#include "detector.hpp"

detector::FileType detector::detect_file_type(const char *filename)
{
    namespace fs = std::filesystem;

    fs::path file_check(filename);

    std::string extension = file_check.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == "")
    {
        return detector::FileType::UNKNOWN;
    }
    else if (extension == ".c")
    {
        return detector::FileType::C;
    }
    else if (extension == ".cpp")
    {
        return detector::FileType::CPP;
    }
    else if (extension == ".py")
    {
        return detector::FileType::PYTHON;
    }
    else if (extension == ".java")
    {
        return detector::FileType::JAVA;
    }
    else if (extension == ".ps1")
    {
        return detector::FileType::POWERSHELL;
    }
    else if (extension == ".bat")
    {
        return detector::FileType::BATCH;
    }
    else if (extension == ".sh")
    {
        return detector::FileType::BASH;
    }
    return detector::FileType::UNKNOWN;
}