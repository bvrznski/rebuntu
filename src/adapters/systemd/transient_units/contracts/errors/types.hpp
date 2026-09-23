#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::transient_units::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/transient_units/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::transient_units::contracts::errors
