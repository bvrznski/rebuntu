#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::cpu::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/cpu/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::cpu::verification::assertions
