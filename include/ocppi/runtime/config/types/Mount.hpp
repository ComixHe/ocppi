// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Mount.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/types/helper.hpp>

namespace ocppi {
namespace runtime {
namespace config {
namespace types {
struct IdMapping;
}
}
}
}

namespace ocppi {
namespace runtime {
namespace config {
namespace types {
using nlohmann::json;

struct Mount {
std::string destination;
std::optional<std::vector<IdMapping>> gidMappings;
std::optional<std::vector<std::string>> options;
std::optional<std::string> source;
std::optional<std::string> type;
std::optional<std::vector<IdMapping>> uidMappings;
};
}
}
}
}

// clang-format on