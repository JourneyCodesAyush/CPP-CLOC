#ifndef cloc_analyzer_hpp
#define cloc_analyzer_hpp

#include "stats.hpp"
#include "comment_syntax.hpp"

namespace analyzer
{
    stats::Stats analyze_files(const char *filename, const comment_syntax::CommentSyntax &syntax);
}

#endif