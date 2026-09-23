#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::ipc::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/ipc/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::ipc::contracts::outputs
