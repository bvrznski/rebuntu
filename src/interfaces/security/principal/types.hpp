#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::principal {
struct PrincipalSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/principal";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::principal
