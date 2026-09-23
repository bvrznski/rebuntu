#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::challenge::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/challenge/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::challenge::verification::assertions
