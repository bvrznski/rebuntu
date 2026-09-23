#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::evidence
