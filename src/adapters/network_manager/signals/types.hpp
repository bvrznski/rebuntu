#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::signals {
struct SignalsSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/signals";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::signals
