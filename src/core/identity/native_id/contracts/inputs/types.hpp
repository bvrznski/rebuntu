#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::native_id::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/identity/native_id/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::native_id::contracts::inputs
