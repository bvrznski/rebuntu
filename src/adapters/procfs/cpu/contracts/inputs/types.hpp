#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::cpu::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/cpu/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::cpu::contracts::inputs
