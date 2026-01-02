#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <string_view>

#include "stats.hpp"
#include "detector.hpp"
#include "result.hpp"

namespace print
{
    struct MetaData
    {
        std::string_view author;
        std::string_view repo_name;
        std::string_view repo_link;
        std::string_view latest_tag;
    };

    inline constexpr MetaData info{"journeycodesayush", "cpp-cloc", "github.com/journeycodesayush/cpp-cloc", "v0.1.0"};

    enum class OutputFormat
    {
        JSON,
        XML,
        CSV,
        STDOUT
    };

    void print_result_map(const result::Result &res, const print::OutputFormat format = print::OutputFormat::JSON);
}
