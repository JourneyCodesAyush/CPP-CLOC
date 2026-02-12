#include "catch2/catch.hpp"

#include "analyzer.hpp"
#include "stats.hpp"
#include "comment_syntax.hpp"
#include <fstream>
#include <filesystem>

TEST_CASE("Single-line comment is counted as comment", "[cpp-cloc]")
{
    const std::string filename = "single_line_comment_is_comment.cpp";

    std::ofstream(filename) << R"(// This is a comment)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 0);
    REQUIRE(stats.lines_of_comment == 1);
    REQUIRE(stats.blank_lines == 0);
    REQUIRE(stats.total() == 1);

    // Cleanup
    std::filesystem::remove(filename);
}

TEST_CASE("Line counted as comment", "[cpp-cloc]")
{
    const std::string filename = "line_count_as_code.cpp";

    std::ofstream(filename) << R"(// int x = 5;)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 0);
    REQUIRE(stats.lines_of_comment == 1);
    REQUIRE(stats.blank_lines == 0);
    REQUIRE(stats.total() == 1);

    // Cleanup
    std::filesystem::remove(filename);
}

TEST_CASE("Blank line", "[cpp-cloc]")
{
    const std::string filename = "blank_line.cpp";

    std::ofstream(filename) << R"(
)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 0);
    REQUIRE(stats.lines_of_comment == 0);
    REQUIRE(stats.blank_lines == 1);
    REQUIRE(stats.total() == 1);

    // Cleanup
    std::filesystem::remove(filename);
}

TEST_CASE("Multi line comments", "[cpp-cloc]")
{
    const std::string filename = "multi_line_comments.cpp";

    std::ofstream(filename) << R"(/*
    this is a multi line comment
    */)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 0);
    REQUIRE(stats.lines_of_comment == 3);
    REQUIRE(stats.blank_lines == 0);
    REQUIRE(stats.total() == 3);

    // Cleanup
    std::filesystem::remove(filename);
}

TEST_CASE("Line counted as code", "[cpp-cloc]")
{
    const std::string filename = "line_counts_as_code.cpp";

    std::ofstream(filename) << R"(int x = 5;)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 1);
    REQUIRE(stats.lines_of_comment == 0);
    REQUIRE(stats.blank_lines == 0);
    REQUIRE(stats.total() == 1);

    // Cleanup
    std::filesystem::remove(filename);
}

TEST_CASE("Inline comments as code", "[cpp-cloc]")
{
    const std::string filename = "inline_comments_as_code.cpp";

    std::ofstream(filename) << R"(int x = 5; // this is an inline comment)";

    auto stats = analyzer::analyze_files(filename, comment_syntax::CLikeComments);

    REQUIRE(stats.lines_of_code == 1);
    REQUIRE(stats.lines_of_comment == 0);
    REQUIRE(stats.blank_lines == 0);
    REQUIRE(stats.total() == 1);

    // Cleanup
    std::filesystem::remove(filename);
}
