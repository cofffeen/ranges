#pragma once

#include "iterators/dir_iterator.h"

class Dir {
public:
  using iterator = DirIterator;
  using value_type = std::iterator_traits<iterator>::value_type;

  Dir(const std::filesystem::path &path, bool recursive = false)
      : begin_(path, recursive), end_(recursive) {}

  iterator begin() const { return begin_; }
  iterator end() const { return end_; }

private:
  iterator begin_;
  iterator end_;
};