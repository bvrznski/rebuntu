#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::feature_negotiation::agreement {
struct AgreementSkeleton final {
    static constexpr std::string_view path = "src/portability/feature_negotiation/agreement";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::feature_negotiation::agreement
