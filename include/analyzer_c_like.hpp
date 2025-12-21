#ifndef cloc_analyzer_c_like_hpp
#define cloc_analyzer_c_like_hpp

#include "stats.hpp"

namespace analyzer
{
    stats::Stats analyze_c(const char *filename);
}

#endif