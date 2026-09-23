#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::verification {
struct VerificationSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/verification";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::verification
