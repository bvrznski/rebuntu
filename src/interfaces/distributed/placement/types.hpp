#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::placement {
struct PlacementSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/placement";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::placement
