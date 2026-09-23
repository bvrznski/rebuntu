#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::principal::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/principal/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::principal::verification::assertions
