#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::drain::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/drain/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::drain::contracts::invariants
