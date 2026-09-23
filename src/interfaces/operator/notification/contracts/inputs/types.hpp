#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::notification::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/notification/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::notification::contracts::inputs
