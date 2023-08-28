// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     SyscallArg.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/helper.hpp>

namespace ocppi {
namespace runtime {
namespace config {
enum class SeccompOperators : int;
}
}
}

namespace ocppi {
namespace runtime {
namespace config {
using nlohmann::json;

struct SyscallArg {
int64_t index;
SeccompOperators op;
int64_t value;
std::optional<int64_t> valueTwo;
};
}
}
}

// clang-format on
