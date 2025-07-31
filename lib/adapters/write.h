#pragma once

template <typename Stream, typename T>
class Write {
public:
  Write(Stream &stream, T delimeter) : stream_(stream), delimeter_(delimeter) {}

  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    for (const auto &value : adapter) {
      stream_ << value << delimeter_;
    }
    return adapter;
  }

private:
  Stream &stream_;
  T delimeter_;
};