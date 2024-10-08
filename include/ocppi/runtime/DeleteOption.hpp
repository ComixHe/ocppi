#pragma once

#include <string>  // for basic_string, string
#include <vector>  // for vector

#include "ocppi/runtime/GlobalOption.hpp"  // for GlobalOption

namespace ocppi::runtime {

struct DeleteOption : public GlobalOption {
  std::vector<std::string> extra;
};

}  // namespace ocppi::runtime
