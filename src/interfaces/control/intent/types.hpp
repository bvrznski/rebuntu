#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::intent {
struct IntentSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/intent";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::intent
