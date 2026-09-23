#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::value {
struct ValueSkeleton final {
    static constexpr std::string_view path = "src/core/result/value";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::value
