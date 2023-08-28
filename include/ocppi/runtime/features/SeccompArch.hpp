// Thish file is generated by /tools/codegen powered by quicktype.
// DO NOT EDIT IT.

// clang-format off

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     SeccompArch.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <ocppi/runtime/features/helper.hpp>

namespace ocppi {
namespace runtime {
namespace features {
using nlohmann::json;

enum class SeccompArch : int { ScmpArchAarch64, ScmpArchArm, ScmpArchMIPS, ScmpArchMips64, ScmpArchMips64N32, ScmpArchMipsel, ScmpArchMipsel64, ScmpArchMipsel64N32, ScmpArchPPC, ScmpArchParisc, ScmpArchParisc64, ScmpArchPpc64, ScmpArchPpc64LE, ScmpArchRiscv64, ScmpArchS390, ScmpArchS390X, ScmpArchX32, ScmpArchX86, ScmpArchX8664 };
}
}
}

// clang-format on
