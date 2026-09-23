#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::confirmation::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/confirmation/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::confirmation::contracts::inputs
