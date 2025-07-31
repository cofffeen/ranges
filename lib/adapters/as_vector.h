#pragma once

#include <vector>

class AsVector {
public:
  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    return std::vector(adapter.begin(), adapter.end());
  }
};
