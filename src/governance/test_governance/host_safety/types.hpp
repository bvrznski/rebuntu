#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::host_safety {
struct HostSafetySkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/host_safety";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::host_safety
