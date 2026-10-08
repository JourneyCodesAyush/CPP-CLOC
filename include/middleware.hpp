#pragma once

#include "detector.hpp"
#include "result.hpp"
#include "stats.hpp"

#include <map>
#include <string>
#include <vector>

namespace middleware {
result::Result process_file(const std::vector<std::string>& files);
}
