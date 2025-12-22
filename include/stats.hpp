#pragma once

#include <string>

namespace stats
{
    struct Stats
    {
        int file_count = 0;
        int lines_of_code = 0;
        int lines_of_comment = 0;
        int blank_lines = 0;
        std::string file_type = "C"; // C was my first language hence ;D

        int total() const
        {
            return lines_of_code + lines_of_comment + blank_lines;
        }

        void merge(const Stats &other)
        {
            file_count += other.file_count;
            lines_of_code += other.lines_of_code;
            lines_of_comment += other.lines_of_comment;
            blank_lines += other.blank_lines;
        }
    };
}
