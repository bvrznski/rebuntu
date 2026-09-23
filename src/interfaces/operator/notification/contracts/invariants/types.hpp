#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::notification::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/notification/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::notification::contracts::invariants
