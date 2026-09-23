#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::redaction::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/system/shell/redaction/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::redaction::verification::evidence
