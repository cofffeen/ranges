#include <processing.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>

TEST(FilterTest, FilterEven) {
  std::vector<int> input = {1, 2, 3, 4, 5};
  auto result =
      AsDataFlow(input) | Filter([](int x) { return x % 2 == 0; }) | AsVector();
  ASSERT_THAT(result, testing::ElementsAre(2, 4));
}

TEST(FilterTest, FilterConst) {
  const std::vector<int> input = {1, 2, 3, 4, 5};
  auto result =
      AsDataFlow(input) | Filter([](int x) { return x % 2 == 0; }) | AsVector();
  ASSERT_THAT(result, testing::ElementsAre(2, 4));
}

TEST(FilterTest, FilterUpperCase) {
  std::vector<std::string> input = {"hello", "world", "HELLO", "WORLD"};
  auto result = AsDataFlow(input) | Filter([](const std::string &x) {
                  return std::all_of(x.begin(), x.end(),
                                     [](char c) { return std::isupper(c); });
                }) |
                AsVector();
  ASSERT_THAT(result, testing::ElementsAre("HELLO", "WORLD"));
}

TEST(FilterTest, FilterExctentions) {
  std::filesystem::current_path(std::filesystem::temp_directory_path());
  std::filesystem::create_directories("filter_test/folder");
  std::ofstream("filter_test/a.txt");
  std::ofstream("filter_test/b.txt");
  std::ofstream("filter_test/c.tsv");
  std::ofstream("filter_test/folder/d.txt");

  bool recursive = true;
  std::filesystem::path path = "filter_test";

  auto result =
      Dir(path, recursive) |
      Filter([](std::filesystem::path p) { return p.extension() == ".txt"; })
      | AsVector();

  std::sort(result.begin(), result.end());

  ASSERT_THAT(result,
              testing::ElementsAre("filter_test/a.txt", "filter_test/b.txt",
                                   "filter_test/folder/d.txt"));

  std::filesystem::remove_all("filter_test");
}