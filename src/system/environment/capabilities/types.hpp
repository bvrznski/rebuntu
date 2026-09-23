#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::capabilities {
struct CapabilitiesSkeleton final {
    static constexpr std::string_view path = "src/system/environment/capabilities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::capabilities
