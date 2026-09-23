#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::native_identity::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/native_identity/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::native_identity::contracts::outputs
