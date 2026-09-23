#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::exception::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/exception/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::exception::contracts::outputs
