#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::target::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/target/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::target::verification::evidence
