// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Storage.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/helper.hpp>

namespace ocppi {
namespace runtime {
namespace config {
using nlohmann::json;

struct Storage {
std::optional<int64_t> bps;
std::optional<int64_t> iops;
std::optional<int64_t> sandboxSize;
};
}
}
}

// clang-format on
