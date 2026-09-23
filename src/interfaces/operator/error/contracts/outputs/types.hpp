#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::error::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/error/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::error::contracts::outputs
