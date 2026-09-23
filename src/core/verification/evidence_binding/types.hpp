#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::evidence_binding {
struct EvidenceBindingSkeleton final {
    static constexpr std::string_view path = "src/core/verification/evidence_binding";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::evidence_binding
