#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::recovery {
struct RecoverySkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/recovery";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::recovery
