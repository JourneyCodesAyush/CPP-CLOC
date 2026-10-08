#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> list_files(const std::string& path,
                                    const std::unordered_set<std::string>& exclude_dir);
