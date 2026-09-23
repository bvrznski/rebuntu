#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::snapshot {
struct SnapshotSkeleton final {
    static constexpr std::string_view path = "src/system/state/snapshot";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::snapshot
