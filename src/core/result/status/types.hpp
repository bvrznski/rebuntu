#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::status {
struct StatusSkeleton final {
    static constexpr std::string_view path = "src/core/result/status";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::status
