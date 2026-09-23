#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::namespace_node::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/namespace/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::namespace_node::contracts::inputs
