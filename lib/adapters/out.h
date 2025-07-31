#pragma once

#include "write.h"

template <typename Stream> 
class Out {
public:
  Out(Stream &stream) : stream_(stream) {}

  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    return adapter | Write(stream_, '\n');
  }

private:
  Stream &stream_;
};
