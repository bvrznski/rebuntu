#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::readiness::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/readiness/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::readiness::verification::assertions
