#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::report::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/report/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::report::contracts::invariants
