// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Linux.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/features/helper.hpp>

#include <ocppi/runtime/features/Apparmor.hpp>
#include <ocppi/runtime/features/Cgroup.hpp>
#include <ocppi/runtime/features/IntelRdt.hpp>
#include <ocppi/runtime/features/Seccomp.hpp>
#include <ocppi/runtime/features/Selinux.hpp>

namespace ocppi {
namespace runtime {
namespace features {
enum class NamespaceType : int;
}
}
}

namespace ocppi {
namespace runtime {
namespace features {
/**
* Linux platform-specific features
*/

using nlohmann::json;

/**
* Linux platform-specific features
*/
struct Linux {
std::optional<Apparmor> apparmor;
std::optional<std::vector<std::string>> capabilities;
std::optional<Cgroup> cgroup;
std::optional<IntelRdt> intelRdt;
std::optional<std::vector<NamespaceType>> namespaces;
std::optional<Seccomp> seccomp;
std::optional<Selinux> selinux;
};
}
}
}

// clang-format on
