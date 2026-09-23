#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::error {
struct ErrorSkeleton final {
    static constexpr std::string_view path = "src/core/result/error";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::error
