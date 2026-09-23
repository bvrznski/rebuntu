#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::manager {
struct ManagerSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/manager";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::manager
