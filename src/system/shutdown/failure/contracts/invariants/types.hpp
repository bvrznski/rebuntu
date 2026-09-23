#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::failure::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/failure/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::failure::contracts::invariants
