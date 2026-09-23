#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::authorization::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/authorization/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::authorization::contracts::invariants
