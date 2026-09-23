#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::goal::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/goal/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::goal::contracts::errors
