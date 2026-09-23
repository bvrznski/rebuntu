#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::error::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/error/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::error::verification::assertions
