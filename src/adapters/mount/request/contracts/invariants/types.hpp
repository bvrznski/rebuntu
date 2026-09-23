#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::request::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/request/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::request::contracts::invariants
