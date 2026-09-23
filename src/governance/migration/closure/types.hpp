#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::closure {
struct ClosureSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/closure";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::closure
