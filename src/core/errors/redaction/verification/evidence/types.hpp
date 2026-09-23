#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::redaction::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/errors/redaction/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::redaction::verification::evidence
