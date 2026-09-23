#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::redaction {
struct RedactionSkeleton final {
    static constexpr std::string_view path = "src/core/errors/redaction";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::redaction
