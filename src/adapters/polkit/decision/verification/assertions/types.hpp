#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::decision::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/decision/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::decision::verification::assertions
