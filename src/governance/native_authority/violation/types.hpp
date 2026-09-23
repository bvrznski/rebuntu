#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::violation {
struct ViolationSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/violation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::violation
