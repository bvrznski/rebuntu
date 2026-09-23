#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::failure {
struct FailureSkeleton final {
    static constexpr std::string_view path = "src/core/verification/failure";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::failure
