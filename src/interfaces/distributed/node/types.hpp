#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::node {
struct NodeSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/node";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::node
