#pragma once

#include "stats.hpp"
#include "detector.hpp"
#include "result.hpp"

#include <vector>
#include <string>
#include <map>

namespace middleware
{
    result::Result process_file(const std::vector<std::string> &files);
}
