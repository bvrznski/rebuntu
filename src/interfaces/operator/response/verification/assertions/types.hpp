#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::response::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/response/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::response::verification::assertions
