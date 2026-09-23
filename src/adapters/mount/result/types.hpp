#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::result {
struct ResultSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/result";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::result
