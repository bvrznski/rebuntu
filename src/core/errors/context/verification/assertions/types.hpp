#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::context::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/errors/context/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::context::verification::assertions
