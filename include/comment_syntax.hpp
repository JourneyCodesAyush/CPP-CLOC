#pragma once

#include <string>

namespace comment_syntax
{
    struct CommentSyntax
    {
        bool supports_multi_line;
        std::string single_line;
        std::string multi_line_start;
        std::string multi_line_end;
    };

    const CommentSyntax CLikeComments{true, "//", "/*", "*/"};
    const CommentSyntax PythonComments{true, "#", "\"\"\"", "\"\"\""};
    const CommentSyntax BashComments{true, "#", "\"\"\"", "\"\"\""};
}
