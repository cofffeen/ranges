#include <processing.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DirTest, NonRecursive) {
  std::filesystem::current_path(std::filesystem::temp_directory_path());
  std::filesystem::create_directories("dir_test/folder");
  std::ofstream("dir_test/a.txt");
  std::ofstream("dir_test/b.txt");
  std::ofstream("dir_test/c.tsv");
  std::ofstream("dir_test/folder/d.txt");

  bool recursive = false;
  std::filesystem::path path = "dir_test";

  auto result = Dir(path, recursive) | AsVector();

  std::sort(result.begin(), result.end());

  ASSERT_THAT(result, testing::ElementsAre("dir_test/a.txt", "dir_test/b.txt",
                                           "dir_test/c.tsv"));
  std::filesystem::remove_all("dir_test");
}

TEST(DirTest, Recursive) {
  std::filesystem::current_path(std::filesystem::temp_directory_path());
  std::filesystem::create_directories("dir_test/folder");
  std::ofstream("dir_test/a.txt");
  std::ofstream("dir_test/b.txt");
  std::ofstream("dir_test/c.tsv");
  std::ofstream("dir_test/folder/d.txt");

  bool recursive = true;
  std::filesystem::path path = "dir_test";

  auto result = Dir(path, recursive) | AsVector();

  std::sort(result.begin(), result.end());

  ASSERT_THAT(result,
              testing::ElementsAre("dir_test/a.txt", "dir_test/b.txt",
                                   "dir_test/c.tsv", "dir_test/folder/d.txt"));
  std::filesystem::remove_all("dir_test");
}
