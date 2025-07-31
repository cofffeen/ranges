#pragma once

#include "range.h"

class OpenFiles {
public:
  template <typename Adapter> 
  auto Update(const Adapter &adapter) {
    return Range<OpenFilesIterator<Adapter>>(
        OpenFilesIterator<Adapter>(adapter.begin(), adapter.end()),
        OpenFilesIterator<Adapter>(adapter.end(), adapter.end()));
  }
};