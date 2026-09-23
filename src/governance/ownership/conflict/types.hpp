#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::conflict {
struct ConflictSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/conflict";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::conflict
