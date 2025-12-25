#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

#include "analyzer.hpp"
#include "comment_syntax.hpp"
#include "stats.hpp"
#include "string_operation_strip.hpp"

// Handles a line inside a multi-line comment
static bool process_inside_multiline(const std::string &line, const comment_syntax::CommentSyntax &syntax, stats::Stats &stat)
{
    if (line.empty())
    {
        stat.blank_lines++;
        return true; // still inside multi-line comment
    }

    size_t end_pos = line.find(syntax.multi_line_end);
    if (end_pos == std::string::npos)
    {
        // Comment continues; no code on this line
        stat.lines_of_comment++;
        return true;
    }

    // Check if there’s code after the comment ends
    std::string after_comment = strip(line.substr(end_pos + syntax.multi_line_end.length()));
    if (after_comment.empty())
        stat.lines_of_comment++;
    else
        stat.lines_of_code++;

    return false; // multi-line comment ends here
}

// Handles a line where multi-line comment starts at the beginning
static bool process_multiline_start_at_beginning(const std::string &line, const comment_syntax::CommentSyntax &syntax, stats::Stats &stat)
{
    size_t end_pos = line.find(syntax.multi_line_end);

    if (end_pos == std::string::npos)
    {
        // Comment starts and continues
        stat.lines_of_comment++;
        return true;
    }

    // Comment ends on same line
    std::string after_comment = strip(line.substr(end_pos + syntax.multi_line_end.length()));
    if (after_comment.empty())
        stat.lines_of_comment++;
    else
        stat.lines_of_code++;

    return false;
}

// Handles a line where multi-line comment starts mid-line (after some code)
static bool process_multiline_start_midline(const std::string &line, const comment_syntax::CommentSyntax &syntax, stats::Stats &stat)
{
    size_t start_pos = line.find(syntax.multi_line_start);
    if (start_pos == std::string::npos)
    {
        // No multi-line start found, treat whole line as code
        stat.lines_of_code++;
        return false;
    }

    // Check if there’s code before the comment starts
    if (start_pos > 0)
        stat.lines_of_code++;
    else
        stat.lines_of_comment++;

    size_t end_pos = line.find(syntax.multi_line_end, start_pos);
    return end_pos == std::string::npos; // true if comment continues
}

stats::Stats analyzer::analyze_files(const std::string &filename, const comment_syntax::CommentSyntax &syntax)
{
    std::ifstream infile(filename);
    std::string line;

    stats::Stats statistic;

    bool inside_multi_line_comment = false;

    if (!infile.is_open())
        return statistic;

    statistic.file_count++;

    while (std::getline(infile, line))
    {
        std::string stripped_line = strip(line);

        if (inside_multi_line_comment)
        {
            inside_multi_line_comment = process_inside_multiline(stripped_line, syntax, statistic);
            continue;
        }

        if (!syntax.single_line.empty() && stripped_line.rfind(syntax.single_line, 0) == 0)
        {
            // Line starts with single-line comment
            statistic.lines_of_comment++;
        }
        else if (syntax.supports_multi_line)
        {
            if (stripped_line.rfind(syntax.multi_line_start, 0) == 0)
            {
                // Multi-line starts at beginning
                inside_multi_line_comment = process_multiline_start_at_beginning(stripped_line, syntax, statistic);
            }
            else if (stripped_line.find(syntax.multi_line_start) != std::string::npos)
            {
                // Multi-line starts mid-line
                inside_multi_line_comment = process_multiline_start_midline(stripped_line, syntax, statistic);
            }
            else if (stripped_line.empty())
            {
                statistic.blank_lines++;
            }
            else
            {
                statistic.lines_of_code++;
            }
        }
        else if (stripped_line.empty())
        {
            statistic.blank_lines++;
        }
        else
        {
            statistic.lines_of_code++;
        }
    }

    return statistic;
}