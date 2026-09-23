#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::request::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/request/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::request::contracts::invariants
