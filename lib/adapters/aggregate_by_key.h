#pragma once

#include <map>
#include <vector>

template <typename T, typename Functor1, typename Functor2> 
class AggregateByKey {
public:
  AggregateByKey(const T &value, const Functor1 &func1, const Functor2 &func2)
      : value_(value), func1_(func1), func2_(func2) {}

  template <typename Adapter> 
  auto Update(const Adapter& adapter) {
    using adapter_iterator = typename Adapter::iterator;
    using adapter_value_type =
        typename std::iterator_traits<adapter_iterator>::value_type;
    using Key = decltype(std::declval<Functor2>()(std::declval<adapter_value_type>()));
    using iterator = std::vector<std::pair<Key, T>>::iterator;
    using reference = std::vector<std::pair<Key, T>>::reference;

    std::vector<std::pair<Key, T>> result;
    std::map<Key, T> result_for_key;
    std::vector<Key> key_order;

    for (adapter_iterator it = adapter.begin(); it != adapter.end(); ++it) {
      Key key = func2_(*it);
      
      if (!result_for_key.contains(key)) {
        key_order.push_back(key);
      }

      func1_(*it, result_for_key[key]);
    }

    for (const Key &key : key_order) {
      result.push_back({key, result_for_key[key]});
    }

    return result;
  }

private:
  T value_;
  Functor1 func1_;
  Functor2 func2_;
};