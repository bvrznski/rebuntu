#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::diagnostic {
struct DiagnosticSkeleton final {
    static constexpr std::string_view path = "src/core/result/diagnostic";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::diagnostic
