#pragma once

#include "range.h"

template <typename Adapter, bool> 
class AsDataFlow;

template <typename Adapter> 
class AsDataFlow<Adapter, true> {
public:
  using iterator = Adapter::const_iterator;
  using value_type = std::iterator_traits<iterator>::value_type;

  AsDataFlow(const Adapter &adapter) : range_(adapter.begin(), adapter.end()) {}

  iterator begin() const { return range_.begin(); }
  iterator end() const { return range_.end(); }

private:
  Range<iterator> range_;
};

template <typename Adapter> 
class AsDataFlow<Adapter, false> {
public:
  using iterator = Adapter::iterator;
  using value_type = std::iterator_traits<iterator>::value_type;

  AsDataFlow(Adapter &adapter) : range_(adapter.begin(), adapter.end()) {}

  iterator begin() const { return range_.begin(); }
  iterator end() const { return range_.end(); }

private:
  Range<iterator> range_;
};

template <typename Adapter>
AsDataFlow(Adapter&) -> AsDataFlow<Adapter, false>;

template <typename Adapter>
AsDataFlow(const Adapter&) -> AsDataFlow<Adapter, true>;

template <typename AdapterLeft, typename AdapterRight>
auto operator|(const AdapterLeft &adapter_left, AdapterRight adapter_right) {
  return adapter_right.Update(adapter_left);
}