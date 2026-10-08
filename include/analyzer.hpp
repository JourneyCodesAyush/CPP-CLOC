#pragma once

#include "comment_syntax.hpp"
#include "stats.hpp"

#include <string>

namespace analyzer {
stats::Stats analyze_files(const std::string& filename,
                           const comment_syntax::CommentSyntax& syntax);
}
