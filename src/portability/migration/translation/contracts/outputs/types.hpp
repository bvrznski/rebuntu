#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::translation::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/translation/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::translation::contracts::outputs
