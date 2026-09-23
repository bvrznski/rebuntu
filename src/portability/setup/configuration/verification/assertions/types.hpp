#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::configuration::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/configuration/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::configuration::verification::assertions
