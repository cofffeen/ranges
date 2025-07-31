#pragma once

class DropNullopt {
public:
  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    return adapter | Filter([](auto value) { return value.has_value(); });
  }
};
