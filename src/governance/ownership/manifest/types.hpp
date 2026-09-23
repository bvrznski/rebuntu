#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::manifest {
struct ManifestSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/manifest";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::manifest
