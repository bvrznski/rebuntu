#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::pid {
struct PidSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/pid";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::pid
