#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::error {
struct ErrorSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/error";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::error
