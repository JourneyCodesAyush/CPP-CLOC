#pragma once

#include <string>

namespace detector
{
    enum class FileType
    {
        C,
        CPP,
        C_CPP_HEADER,
        JAVA,
        PYTHON,
        JAVASCRIPT,
        TYPESCRIPT,
        BASH,
        POWERSHELL,
        BATCH,
        UNKNOWN
    };

    FileType detect_file_type(const std::string &filename);
}
