#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::scope {
struct ScopeSkeleton final {
    static constexpr std::string_view path = "src/core/identity/scope";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::scope
