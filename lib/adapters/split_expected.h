#pragma once

#include <vector>

template <typename Functor> 
class SplitExpected {
public:
  SplitExpected(Functor func) : func_(func) {}

  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    using iterator = typename Adapter::iterator;
    using expected_type = typename std::iterator_traits<iterator>::value_type;
    using value_type = typename expected_type::value_type;
    using error_type = typename expected_type::error_type;

    std::vector<value_type> values;
    std::vector<error_type> errors;

    for (const expected_type &value : adapter) {
      if (value.has_value()) {
        values.push_back(value.value());
      } else {
        errors.push_back(value.error());
      }
    }

    return std::make_pair(errors, values);
  }

private:
  Functor func_;
};