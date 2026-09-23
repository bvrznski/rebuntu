#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::mounts::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/mounts/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::mounts::contracts::inputs
