#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::verification {
struct VerificationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/verification";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::verification
