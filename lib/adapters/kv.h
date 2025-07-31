#pragma once

template <typename Key, typename Value> 
struct KV {
  Key key;
  Value value;

  bool operator==(const KV &other) const = default;
};