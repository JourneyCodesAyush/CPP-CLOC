#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <filesystem>

std::vector<std::string> list_files(const std::string &path, const std::unordered_set<std::string> &exclude_dir);