#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::process::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/process/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::process::verification::assertions
