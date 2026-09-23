#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::bundle {
struct BundleSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/bundle";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::bundle
