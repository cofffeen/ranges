#include <processing.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct Employee {
    uint64_t department_id;
    std::string name;

    bool operator==(const Employee& other) const = default;
};

TEST(AggregateByKeyTest, CountingAggregatedValues) {
    std::vector<std::string> input = {"name4", "name0", "name1", "name0", "name2", "name0", "name1"};

    auto result =
        AsDataFlow(input)
            | AggregateByKey(
                std::size_t{0},
                [](const std::string&, std::size_t& accumulated) { ++accumulated; },
                [](const std::string& token) { return token; }
            )
            | AsVector();

    ASSERT_THAT(
        result,
        ::testing::ElementsAre(
            std::make_pair("name4", 1),
            std::make_pair("name0", 3),
            std::make_pair("name1", 2),
            std::make_pair("name2", 1)
        )
    );
}

TEST(AggregateByKeyTest, AggregatingWithSeveralOutputsForEachKey) {
    std::vector<Employee> employees = {
        {3, "name1"},
        {1, "name1"},
        {1, "name2"},
        {2, "name1"},
        {2, "name2"},
        {2, "name3"}
    };

    auto result =
        AsDataFlow(employees)
            | AggregateByKey(
                std::vector<Employee>{},
                [](const Employee& employee, std::vector<Employee>& accumulated) {
                    if (accumulated.size() == 2) {
                        return;
                    }
                    accumulated.push_back(employee);
                },
                [](const Employee& employee) { return employee.department_id; }
            )
            | AsVector();

    ASSERT_THAT(
        result,
        ::testing::ElementsAre(
            std::make_pair(3, std::vector<Employee>{Employee{3, "name1"}}),
            std::make_pair(1, std::vector<Employee>{Employee{1, "name1"}, Employee{1, "name2"}}),
            std::make_pair(2, std::vector<Employee>{Employee{2, "name1"}, Employee{2, "name2"}})
        )
    );
}

TEST(AggregateByKeyTest, WordCount) {
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

  std::stringstream file_emulator;
  Dir(path, recursive) |
      Filter([](std::filesystem::path p) { return p.extension() == ".txt"; }) |
      OpenFiles() | Split("\n ,.;") | Transform([](std::string token) {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](char c) { return std::tolower(c); });
        return token;
      }) |
      AggregateByKey(
          0uz, [](std::string, size_t &count) { ++count; },
          [](std::string token) { return token; }) |
      Transform([](std::pair<std::string, size_t> stat) {
        return std::format("{} - {}", stat.first, stat.second);
      }) |
      Out(file_emulator);

  ASSERT_EQ(file_emulator.str(),
            "c - 1\nooo - 1\na - 1\nccc - 1\nb - 1\nbbb - 2\naaa - 3\n");

  std::filesystem::remove_all("dir_test");
}
