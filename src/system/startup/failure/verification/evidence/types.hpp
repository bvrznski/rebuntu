#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::failure::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/system/startup/failure/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::failure::verification::evidence
