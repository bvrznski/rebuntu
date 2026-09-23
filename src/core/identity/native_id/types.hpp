#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::native_id {
struct NativeIdSkeleton final {
    static constexpr std::string_view path = "src/core/identity/native_id";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::native_id
