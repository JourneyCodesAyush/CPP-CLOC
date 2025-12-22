#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

std::string strip(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

void cloc_cpp(const char *filename)
{
    std::ifstream infile(filename);

    std::string line;

    int lines_of_code = 0;
    int lines_of_comment = 0;
    int blank_lines = 0;

    bool inside_multi_line_comment = false;

    if (infile.is_open())
    {
        while (std::getline(infile, line))
        {
            // line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            line = strip(line);
            // std::cout << line << "\n";

            if (inside_multi_line_comment)
            {
                lines_of_comment++;
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
                    lines_of_comment++;
                }

                else if (line.size() >= 2 and line.compare(0, 2, "/*") == 0)
                {
                    lines_of_comment++;
                    inside_multi_line_comment = true;
                }

                // else if (line.find_first_not_of(" \t\r\n") == std::string::npos)
                else if (line.empty())
                {
                    blank_lines++;
                }
                else
                {
                    lines_of_code++;
                }
            }
        }
    }

    // std::cout << "Code | Comments | Blank lines | Total lines\n";
    // std::cout << lines_of_code << " | " << lines_of_comment << " | " << blank_lines
    //           << " | " << (lines_of_code + lines_of_comment + blank_lines) << "\n";

    std::cout << std::right << std::setw(6) << "Code"
              << " | " << std::setw(8) << "Comments"
              << " | " << std::setw(12) << "Blank lines"
              << " | " << std::setw(11) << "Total lines" << "\n";

    std::cout << std::setw(6) << lines_of_code
              << " | " << std::setw(8) << lines_of_comment
              << " | " << std::setw(12) << blank_lines
              << " | " << std::setw(11) << (lines_of_code + lines_of_comment + blank_lines) << "\n";
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        printf("Some new file is there. %s\n", argv[1]);
        // printf("%s", argv[1]);
        cloc_cpp(argv[1]);
    }
    return 0;
}
