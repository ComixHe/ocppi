// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     PersonalityDomain.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/helper.hpp>

namespace ocppi {
namespace runtime {
namespace config {
using nlohmann::json;

enum class PersonalityDomain : int { Linux, Linux32 };
}
}
}

// clang-format on
