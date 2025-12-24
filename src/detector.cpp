#include <string>
#include <cctype>
#include <algorithm>
#include <filesystem>

#include "detector.hpp"

detector::FileType detector::detect_file_type(const std::string &filename)
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
    else if (extension == ".h" or extension == ".hpp")
    {
        return detector::FileType::C_CPP_HEADER;
    }
    else if (extension == ".py")
    {
        return detector::FileType::PYTHON;
    }
    else if (extension == ".html")
    {
        return detector::FileType::HTML;
    }
    else if (extension == ".md")
    {
        return detector::FileType::MARKDOWN;
    }
    else if (extension == ".js")
    {
        return detector::FileType::JAVASCRIPT;
    }
    else if (extension == ".ts")
    {
        return detector::FileType::TYPESCRIPT;
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