#pragma once

#include "kv.h"
#include "join_result.h"

template <typename AdapterJoined, typename FuncBase,
          typename FuncJoined>
class Join {
public:
  Join(const AdapterJoined &joined) : joined_(joined) {}
  Join(const AdapterJoined &joined, const FuncBase &func_base,
       const FuncJoined &func_joined)
      : joined_(joined), func_base_(func_base), func_joined_(func_joined) {}

  template <typename AdapterBase> 
  auto Update(const AdapterBase &base) {
    using Base =
        std::iterator_traits<typename AdapterBase::iterator>::value_type;
    using Joined =
        std::iterator_traits<typename AdapterJoined::iterator>::value_type;

    std::vector<JoinResult<Base, Joined>> result;

    for (auto b : base) {
      JoinResult<Base, Joined> res = {b, std::nullopt};
      for (auto j : joined_) {
        if (func_base_(b) == func_joined_(j)) {
          res = JoinResult<Base, Joined>{b, j};
          break;
        }
      }

      result.push_back(res);
    }

    return result;
  }

private:
  AdapterJoined joined_;
  FuncBase func_base_;
  FuncJoined func_joined_;
};

template <typename AdapterJoined> 
class Join<AdapterJoined, void, void> {
public:
  Join(const AdapterJoined &joined) : joined_(joined) {}

  template <typename AdapterBase> 
  auto Update(const AdapterBase &base) {
    using Base = decltype((*base.begin()).value);
    using Joined = decltype((*joined_.begin()).value);

    std::vector<JoinResult<Base, Joined>> result;

    for (auto b : base) {
      JoinResult<Base, Joined> res = {b.value, std::nullopt};
      for (auto j : joined_) {
        if (b.key == j.key) {
          res = {b.value, j.value};
          break;
        }
      }

      result.push_back(res);
    }

    return result;
  }

private:
  AdapterJoined joined_;
};

template <typename AdapterJoined>
Join(AdapterJoined) -> Join<AdapterJoined, void, void>;