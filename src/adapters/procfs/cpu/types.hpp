#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::cpu {
struct CpuSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/cpu";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::cpu
