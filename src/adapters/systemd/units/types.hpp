#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::units {
struct UnitsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/units";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::units
