#pragma once

#include <exception>
#include <filesystem>
#include <memory>

#include "ocppi/cli/CommonCLI.hpp"
#include "tl/expected.hpp"

namespace spdlog
{
class logger;
} // namespace spdlog

namespace ocppi::cli::runc
{

class Runc : public CommonCLI {
        using CommonCLI::CommonCLI;

    public:
        static auto New(const std::filesystem::path &bin) noexcept
                -> tl::expected<std::unique_ptr<Runc>, std::exception_ptr>;

        static auto New(const std::filesystem::path &bin,
                        const std::shared_ptr<spdlog::logger> &logger) noexcept
                -> tl::expected<std::unique_ptr<Runc>, std::exception_ptr>;
};

}
