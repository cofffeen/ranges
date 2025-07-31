#include <processing.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(OpenFilesTest, OpenFiles) {
  std::filesystem::current_path(std::filesystem::temp_directory_path());
  std::filesystem::create_directories("dir_test/folder");
  std::ofstream fouta("dir_test/a.txt", std::ios::out);
  fouta << "Aaa aaa BBb\nAAA";
  fouta.close();

  std::ofstream foutb("dir_test/b.txt");
  foutb << "CCc B,bbb";
  foutb.close();

  std::ofstream foutc("dir_test/folder/c.txt");
  foutc << "c ooo a";
  foutc.close();

  bool recursive = true;
  std::filesystem::path path = "dir_test";

  auto result =
      Dir(path, recursive) | OpenFiles() | Split("\n ,.;") | AsVector();

  std::sort(result.begin(), result.end());

  ASSERT_THAT(result, testing::ElementsAre("AAA", "Aaa", "B", "BBb", "CCc", "a",
                                           "aaa", "bbb", "c", "ooo"));

  std::filesystem::remove_all("dir_test");
}