// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     IdMapping.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/helper.hpp>

namespace ocppi {
namespace runtime {
namespace config {
using nlohmann::json;

struct IdMapping {
int64_t containerID;
int64_t hostID;
int64_t size;
};
}
}
}

// clang-format on
