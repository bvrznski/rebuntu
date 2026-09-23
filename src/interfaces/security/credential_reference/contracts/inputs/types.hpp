#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::credential_reference::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/credential_reference/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::credential_reference::contracts::inputs
