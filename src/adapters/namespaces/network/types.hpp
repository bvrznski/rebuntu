#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::network {
struct NetworkSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/network";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::network
