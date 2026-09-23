#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::rollback::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/install/rollback/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::rollback::verification::evidence
