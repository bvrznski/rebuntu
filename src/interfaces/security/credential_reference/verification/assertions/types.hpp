#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::credential_reference::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/credential_reference/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::credential_reference::verification::assertions
