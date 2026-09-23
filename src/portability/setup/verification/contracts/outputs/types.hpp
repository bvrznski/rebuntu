#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::verification::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/verification/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::verification::contracts::outputs
