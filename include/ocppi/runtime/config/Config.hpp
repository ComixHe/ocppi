// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Config.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/config/helper.hpp>

#include <ocppi/runtime/config/Hooks.hpp>
#include <ocppi/runtime/config/Linux.hpp>
#include <ocppi/runtime/config/Process.hpp>
#include <ocppi/runtime/config/Root.hpp>
#include <ocppi/runtime/config/Solaris.hpp>
#include <ocppi/runtime/config/Vm.hpp>
#include <ocppi/runtime/config/Windows.hpp>
#include <ocppi/runtime/config/Zos.hpp>

namespace ocppi {
namespace runtime {
namespace config {
struct Mount;
}
}
}

namespace ocppi {
namespace runtime {
namespace config {
/**
* Open Container Initiative Runtime Specification Container Configuration Schema
*/

using nlohmann::json;

/**
* Open Container Initiative Runtime Specification Container Configuration Schema
*/
struct Config {
std::optional<std::map<std::string, nlohmann::json>> annotations;
std::optional<std::string> domainname;
std::optional<Hooks> hooks;
std::optional<std::string> hostname;
std::optional<Linux> linux;
std::optional<std::vector<Mount>> mounts;
std::string ociVersion;
std::optional<Process> process;
/**
* Configures the container's root filesystem.
*/
std::optional<Root> root;
std::optional<Solaris> solaris;
std::optional<Vm> vm;
std::optional<Windows> windows;
std::optional<Zos> zos;
};
}
}
}

// clang-format on
