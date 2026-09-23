#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::persistence::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/state/persistence/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::persistence::verification::assertions
