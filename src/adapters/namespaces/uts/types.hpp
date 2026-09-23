#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::uts {
struct UtsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/uts";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::uts
