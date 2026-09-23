#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::error {
struct ErrorSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/error";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::error
