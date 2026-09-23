#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::process {
struct ProcessSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/process";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::process
