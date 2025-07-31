#pragma once

#include "range.h"

template <typename Functor> 
class Filter {
public:
  Filter(const Functor &func) : func_(func) {}

  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    return Range<FilterIterator<Adapter, Functor>>(
        FilterIterator<Adapter, Functor>(adapter.begin(), adapter.end(), func_),
        FilterIterator<Adapter, Functor>(adapter.end(), adapter.end(), func_));
  }

private:
  Functor func_;
};
