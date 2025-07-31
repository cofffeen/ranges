#pragma once

#include <filesystem>
#include <iostream>
#include <variant>
#include <map>
#include <vector>
#include <fstream>

#include "adapters/iterators/dir_iterator.h"
#include "adapters/iterators/filter_iterator.h"
#include "adapters/iterators/open_files_iterator.h"
#include "adapters/iterators/split_iterator.h"
#include "adapters/iterators/transform_iterator.h"

#include "adapters/range.h"
#include "adapters/aggregate_by_key.h"
#include "adapters/as_vector.h"
#include "adapters/dir.h"
#include "adapters/filter.h"
#include "adapters/drop_nullopt.h"
#include "adapters/kv.h"
#include "adapters/join_result.h"
#include "adapters/join.h"
#include "adapters/open_files.h"
#include "adapters/write.h"
#include "adapters/out.h"
#include "adapters/split.h"
#include "adapters/split_expected.h"
#include "adapters/transform.h"
#include "adapters/as_data_flow.h"