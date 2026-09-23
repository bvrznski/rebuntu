#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::desired::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/state/desired/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::desired::contracts::inputs
