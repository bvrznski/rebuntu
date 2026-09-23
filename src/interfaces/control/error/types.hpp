#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::error {
struct ErrorSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/error";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::error
