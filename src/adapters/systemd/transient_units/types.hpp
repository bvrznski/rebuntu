#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::transient_units {
struct TransientUnitsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/transient_units";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::transient_units
