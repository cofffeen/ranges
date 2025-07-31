#pragma once

#include <filesystem>
#include <variant>

class DirIterator {
public:
  using value_type = std::filesystem::path;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;
  using reference = value_type;

  DirIterator(const value_type &path, bool recursive) {
    if (recursive) {
      begin_ = std::filesystem::recursive_directory_iterator(path);
    } else {
      begin_ = std::filesystem::directory_iterator(path);
    }
    SkipDir();
  }

  DirIterator(bool recursive) {
    if (recursive) {
      begin_ = std::filesystem::recursive_directory_iterator();
    } else {
      begin_ = std::filesystem::directory_iterator();
    }
  }

  DirIterator(const DirIterator &other) : begin_(other.begin_) {}

  ~DirIterator() = default;

  DirIterator &operator=(const DirIterator &other) {
    begin_ = other.begin_;

    return *this;
  }

  reference operator*() const {
    if (std::holds_alternative<std::filesystem::directory_iterator>(begin_)) {
      if (std::get<std::filesystem::directory_iterator>(begin_) !=
          std::filesystem::directory_iterator()) {
        return std::get<std::filesystem::directory_iterator>(begin_)->path();
      }
    }

    return std::get<std::filesystem::recursive_directory_iterator>(begin_)
        ->path();
  }

  bool operator==(const DirIterator &other) const {
    return (begin_ == other.begin_);
  }

  bool operator!=(const DirIterator &other) const { return !(*this == other); }

  DirIterator &operator++() {
    if (std::holds_alternative<std::filesystem::directory_iterator>(begin_)) {
      if (std::get<std::filesystem::directory_iterator>(begin_) !=
          std::filesystem::directory_iterator()) {
        ++std::get<std::filesystem::directory_iterator>(begin_);
      }
    } else if (std::get<std::filesystem::recursive_directory_iterator>(
                   begin_) != std::filesystem::recursive_directory_iterator()) {
      ++std::get<std::filesystem::recursive_directory_iterator>(begin_);
    }

    SkipDir();
    return *this;
  }

  DirIterator operator++(int) {
    DirIterator copy = *this;
    ++(*this);
    return copy;
  }

private:
  std::variant<std::filesystem::recursive_directory_iterator,
               std::filesystem::directory_iterator>
      begin_;

  void SkipDir() {
    if (std::holds_alternative<std::filesystem::directory_iterator>(begin_)) {
      while (std::get<std::filesystem::directory_iterator>(begin_) !=
                 std::filesystem::directory_iterator() &&
             std::get<std::filesystem::directory_iterator>(begin_)
                 ->is_directory()) {
        ++std::get<std::filesystem::directory_iterator>(begin_);
      }
    } else {
      while (std::get<std::filesystem::recursive_directory_iterator>(begin_) !=
                 std::filesystem::recursive_directory_iterator() &&
             std::get<std::filesystem::recursive_directory_iterator>(begin_)
                 ->is_directory()) {
        ++std::get<std::filesystem::recursive_directory_iterator>(begin_);
      }
    }
  }
};