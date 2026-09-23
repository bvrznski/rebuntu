#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::error {
struct ErrorSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/error";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::error
