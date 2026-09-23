#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::memory {
struct MemorySkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/memory";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::memory
