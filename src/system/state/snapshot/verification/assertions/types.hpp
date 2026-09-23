#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::snapshot::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/state/snapshot/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::snapshot::verification::assertions
