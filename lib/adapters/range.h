#pragma once

#include "iterators/filter_iterator.h"
#include "iterators/open_files_iterator.h"
#include "iterators/split_iterator.h"
#include "iterators/transform_iterator.h"

template <typename InputIterator>
class Range {
public:
  using adapter_iterator = InputIterator;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;
  using reference = adapter_iterator &;
  using iterator = InputIterator;

  Range(const iterator &begin, const iterator &end)
      : begin_(begin), end_(end) {}

  iterator begin() const { return begin_; }
  iterator end() const { return end_; }

private:
  iterator begin_;
  iterator end_;
};