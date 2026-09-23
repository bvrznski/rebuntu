#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::hierarchy::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/hierarchy/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::hierarchy::contracts::errors
