#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::native {
struct NativeSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/native";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::native
