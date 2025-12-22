#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAtEnd(FILE *fp)
{
    return feof(fp);
}

char peek(FILE *fp)
{
    long pos = ftell(fp);
    if (isAtEnd(fp))
    {
        return '\0';
    }
    char buffer;
    buffer = fgetc(fp);
    fseek(fp, pos, SEEK_SET);
    return buffer;
}

char peekNext(FILE *fp)
{
    long pos = ftell(fp);
    if (isAtEnd(fp))
    {
        return '\0';
    }
    char buffer;
    fgetc(fp);
    buffer = fgetc(fp);
    fseek(fp, pos, SEEK_SET);
    return buffer;
}

void c_cloc(const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file: %s\n", filename);
    }

    int lines_of_code = 0;
    int lines_of_comment = 0;
    int blank_lines = 0;
    printf("Opened the file...\n");
    char c;
    while (!isAtEnd(fp))
    {
        c = fgetc(fp);
        printf("%c", c);
        if (c == '/' && peek(fp) == '/')
        {
            ++lines_of_comment;
            // break;

            while (fgetc(fp) != '\n')
            {
                // Do nothing
                if (isAtEnd(fp))
                {
                    break;
                }
                c = fgetc(fp);
            }
        }
        // else if (c == '/' && peek(fp) == '*')
        // {
        //     ++lines_of_comment;
        //     c = fgetc(fp);
        //     if (c == '\n')
        //     {
        //         ++lines_of_comment;
        //     }
        //     while (c != '*' && peek(fp) != '/')
        //     {
        //         // while (!isAtEnd(fp) && fgetc(fp) != '*' && fgetc(fp) != '/')
        //         // {
        //         //     // Do nothing
        //         //     if (fgetc(fp) == '\n')
        //         //     {
        //         //         ++lines_of_comment;
        //         //         // break;
        //         //     }
        //         // }
        //         char intermediate = fgetc(fp);

        //         if (intermediate == '\n')
        //         {
        //             ++lines_of_comment;
        //         }
        //     }
        //     fgetc(fp);
        //     fgetc(fp);
        //     // break;
        // }
        else if (c == '/' && (peek(fp) != '*' || peek(fp) != '/'))
        {
            ++lines_of_code;
            // TODO: Count number of lines of code
        }
    }

    fseek(fp, 0, SEEK_SET);

    while (!isAtEnd(fp))
    {
        // printf("Inside second while loop for multi line comment.\n");
        c = fgetc(fp);
        if (c == '/' && peek(fp) == '*')
        {
            ++lines_of_comment;
            c = fgetc(fp);
            if (c == '\n')
            {
                ++lines_of_comment;
            }
            while (c != '*' && peek(fp) != '/')
            {
                c = fgetc(fp);

                if (c == '\n')
                {
                    ++lines_of_comment;
                }
            }
            fgetc(fp);
            fgetc(fp);
            // break;
        }
    }

    fclose(fp);
    printf("Closed the file...\n");
    printf("Lines of code, Lines of comment, Blank lines\n");
    printf("%d\t %d\t %d\n", lines_of_code, lines_of_comment, blank_lines);
}

void c_cloc_line_wise(const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file: %s\n", filename);
    }

    int lines_of_code = 0;
    int lines_of_comment = 0;
    int blank_lines = 0;
    printf("Opened the file...\n");

    // char buffer[256];
    // while (fgets(buffer, sizeof(buffer), fp) != NULL)
    // {
    // }

    fclose(fp);
    printf("Closed the file...\n");
    printf("Lines of code, Lines of comment, Blank lines\n");
    printf("%d %d %d", lines_of_code, lines_of_comment, blank_lines);
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        printf("Some new file is there. %s\n", argv[1]);
        // printf("%s", argv[1]);
        c_cloc(argv[1]);
    }
    return 0;
}
