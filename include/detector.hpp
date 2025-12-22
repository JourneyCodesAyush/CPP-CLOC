#pragma once

#include <string>

namespace detector
{
    enum class FileType
    {
        C,
        CPP,
        JAVA,
        PYTHON,
        BASH,
        POWERSHELL,
        BATCH,
        UNKNOWN
    };

    FileType detect_file_type(const std::string &filename);
}
