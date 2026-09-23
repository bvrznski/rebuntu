#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/result/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::evidence
