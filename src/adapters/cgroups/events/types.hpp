#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::events {
struct EventsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/events";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::events
