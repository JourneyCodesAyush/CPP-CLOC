#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

#include "analyzer.hpp"
#include "comment_syntax.hpp"
#include "stats.hpp"
#include "string_operation_strip.hpp"

stats::Stats analyzer::analyze_files(const std::string &filename, const comment_syntax::CommentSyntax &syntax)
{
    std::ifstream infile(filename);
    std::string line;

    stats::Stats statistic;

    bool inside_multi_line_comment = false;

    if (infile.is_open())
    {
        statistic.file_count += 1;
        if (syntax.supports_multi_line)
        {
            while (std::getline(infile, line))
            {
                line = strip(line);

                if (inside_multi_line_comment)
                {
                    statistic.lines_of_comment++;
                    if (line.size() >= 2 and line.compare(line.size() - syntax.multi_line_end.length(), syntax.multi_line_end.length(), syntax.multi_line_end) == 0)
                    {
                        inside_multi_line_comment = false;
                    }
                    continue;
                }
                else
                {
                    if (line.size() >= syntax.single_line.length() and line.compare(0, syntax.single_line.length(), syntax.single_line) == 0)
                    {
                        statistic.lines_of_comment++;
                    }
                    else if (line.size() >= syntax.multi_line_start.length() and line.compare(0, syntax.multi_line_start.length(), syntax.multi_line_start) == 0)
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
        else
        {
            while (std::getline(infile, line))
            {
                line = strip(line);
                if (line.size() >= syntax.single_line.length() and line.compare(0, syntax.single_line.length(), syntax.single_line) == 0)
                {
                    statistic.lines_of_comment++;
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