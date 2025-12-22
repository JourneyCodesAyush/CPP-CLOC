#pragma once

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

    FileType detect_file_type(const char *filename);
}
