#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::provider {
struct ProviderSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/provider";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::provider
