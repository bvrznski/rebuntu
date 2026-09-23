#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::response::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/response/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::response::contracts::invariants
