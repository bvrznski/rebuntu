#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::user::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/user/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::user::contracts::inputs
