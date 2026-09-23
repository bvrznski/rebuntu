#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::uts::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/uts/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::uts::contracts::outputs
