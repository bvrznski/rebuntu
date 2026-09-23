#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::validation::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/validation/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::validation::verification::evidence
