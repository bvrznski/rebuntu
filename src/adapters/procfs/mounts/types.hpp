#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::mounts {
struct MountsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/mounts";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::mounts
