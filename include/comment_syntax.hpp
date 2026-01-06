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

    inline const CommentSyntax AssemblyComments{false, ";", ""};
    inline const CommentSyntax CLikeComments{true, "//", "/*", "*/"};
    inline const CommentSyntax PythonComments{true, "#", "\"\"\"", "\"\"\""};
    inline const CommentSyntax BashYMLComments{false, "#", "", ""};
    inline const CommentSyntax PowerShellComments{false, "#", "<#", "#>"};
    inline const CommentSyntax HTMLMarkdownComments{false, "", "<!--", "-->"};
    inline const CommentSyntax CssSyntax{true, "", "/*", "*/"};
}
