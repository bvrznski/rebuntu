#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::persistence {
struct PersistenceSkeleton final {
    static constexpr std::string_view path = "src/system/state/persistence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::persistence
