#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::error_mapping::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/error_mapping/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::error_mapping::contracts::outputs
