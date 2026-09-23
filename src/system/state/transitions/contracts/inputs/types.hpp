#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::transitions::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/state/transitions/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::transitions::contracts::inputs
