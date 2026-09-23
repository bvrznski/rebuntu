#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::provenance {
struct ProvenanceSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/provenance";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::provenance
