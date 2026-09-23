#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::binding {
struct BindingSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/binding";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::binding
