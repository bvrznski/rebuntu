#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::snapshot {
struct SnapshotSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/snapshot";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::snapshot
