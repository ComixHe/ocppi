// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     NamespaceType.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/features/helper.hpp>

namespace ocppi {
namespace runtime {
namespace features {
using nlohmann::json;

enum class NamespaceType : int { Cgroup, Ipc, Mount, Network, Pid, Time, User, Uts };
}
}
}

// clang-format on
