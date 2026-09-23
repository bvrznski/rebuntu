#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::verification::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/verification/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::verification::contracts::errors
