#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::evidence::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/result/evidence/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::evidence::contracts::errors
