#pragma once

#include "range.h"

template <typename Functor> 
class Transform {
public:
  Transform(Functor func) : func_(func) {}

  template <typename Adapter>
  auto Update(const Adapter &adapter) {
    return Range<TransformIterator<Adapter, Functor>>(
        TransformIterator<Adapter, Functor>(adapter.begin(), adapter.end(),
                                            func_),
        TransformIterator<Adapter, Functor>(adapter.end(), adapter.end(),
                                            func_));
  }

private:
  Functor func_;
};