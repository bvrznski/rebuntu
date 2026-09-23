#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::observation {
struct ObservationSkeleton final {
    static constexpr std::string_view path = "src/system/units/observation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::observation
