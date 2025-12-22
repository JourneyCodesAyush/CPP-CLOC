#pragma once

#include <string>
#include "stats.hpp"
#include "comment_syntax.hpp"

namespace analyzer
{
    stats::Stats analyze_files(const std::string &filename, const comment_syntax::CommentSyntax &syntax);
}
