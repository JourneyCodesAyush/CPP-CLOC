#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

#include "analyzer_c_like.hpp"
#include "stats.hpp"
#include "string_operation_strip.hpp"

stats::Stats analyzer::analyze_c(const char *filename)
{
    std::ifstream infile(filename);
    std::string line;

    stats::Stats statistic;

    bool inside_multi_line_comment = false;

    if (infile.is_open())
    {
        statistic.file_count += 1;
        while (std::getline(infile, line))
        {
            line = strip(line);

            if (inside_multi_line_comment)
            {
                statistic.lines_of_comment++;
                if (line.size() >= 2 and line.compare(line.size() - 2, 2, "*/") == 0)
                {
                    inside_multi_line_comment = false;
                }
                continue;
            }
            else
            {
                if (line.size() >= 2 and line.compare(0, 2, "//") == 0)
                {
                    statistic.lines_of_comment++;
                }
                else if (line.size() >= 2 and line.compare(0, 2, "/*") == 0)
                {
                    statistic.lines_of_comment++;
                    inside_multi_line_comment = true;
                }
                else if (line.empty())
                {
                    statistic.blank_lines++;
                }
                else
                {
                    statistic.lines_of_code++;
                }
            }
        }
    }

    return statistic;
}