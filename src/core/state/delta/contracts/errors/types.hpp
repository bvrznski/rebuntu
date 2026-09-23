#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::delta::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/state/delta/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::delta::contracts::errors
