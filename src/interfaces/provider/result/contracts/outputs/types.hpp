#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::result::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/result/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::result::contracts::outputs
