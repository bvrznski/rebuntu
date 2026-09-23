#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::interface::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/interface/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::interface::verification::assertions
