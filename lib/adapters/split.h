#pragma once

#include "range.h"

class Split {
public:
  using value_type = std::string;

  Split(const std::string &delimeter) : delimeter_(delimeter) {}

  template <typename Adapter>
  auto Update(const Adapter &adapter) {
    return Range<SplitIterator<Adapter>>(
        SplitIterator<Adapter>(adapter.begin(), adapter.end(), delimeter_),
        SplitIterator<Adapter>(adapter.end(), adapter.end(), delimeter_));
  }

private:
  const std::string &delimeter_;
};