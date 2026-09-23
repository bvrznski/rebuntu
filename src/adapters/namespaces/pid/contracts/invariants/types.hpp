#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::pid::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/pid/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::pid::contracts::invariants
