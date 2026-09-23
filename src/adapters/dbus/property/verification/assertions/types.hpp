#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::property::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/property/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::property::verification::assertions
