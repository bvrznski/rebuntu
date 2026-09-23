#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::authorization {
struct AuthorizationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/authorization";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::authorization
