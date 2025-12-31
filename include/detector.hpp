#pragma once

#include <string>

namespace detector
{
    enum class FileType
    {
        ASSEMBLY,
        C,
        CPP,
        C_CPP_HEADER,
        JAVA,
        PYTHON,
        HTML,
        MARKDOWN,
        CSS,
        JAVASCRIPT,
        TYPESCRIPT,
        JSON,
        BASH,
        POWERSHELL,
        BATCH,
        UNKNOWN
    };

    FileType detect_file_type(const std::string &filename);
}
