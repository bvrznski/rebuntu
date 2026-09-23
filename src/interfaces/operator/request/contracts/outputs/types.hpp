#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::request::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/request/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::request::contracts::outputs
