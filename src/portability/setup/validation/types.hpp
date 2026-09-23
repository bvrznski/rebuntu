#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::validation {
struct ValidationSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/validation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::validation
