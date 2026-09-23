#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::delta {
struct DeltaSkeleton final {
    static constexpr std::string_view path = "src/core/state/delta";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::delta
