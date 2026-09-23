#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::desired_state::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/system/units/desired_state/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::desired_state::contracts::errors
