#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::confirmation::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/confirmation/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::confirmation::contracts::outputs
