#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::feature_negotiation::degradation::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/feature_negotiation/degradation/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::feature_negotiation::degradation::contracts::errors
