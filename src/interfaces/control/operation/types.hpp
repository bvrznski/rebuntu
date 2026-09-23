#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::operation {
struct OperationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/operation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::operation
