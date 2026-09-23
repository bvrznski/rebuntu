#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::signals {
struct SignalsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/signals";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::signals
