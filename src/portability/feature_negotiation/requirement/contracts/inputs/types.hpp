#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::feature_negotiation::requirement::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/feature_negotiation/requirement/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::feature_negotiation::requirement::contracts::inputs
