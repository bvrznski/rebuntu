#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::rollback::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/rollback/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::rollback::verification::assertions
