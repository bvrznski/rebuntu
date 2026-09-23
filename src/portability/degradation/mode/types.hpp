#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::mode {
struct ModeSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/mode";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::mode
