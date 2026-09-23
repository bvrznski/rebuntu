#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::session::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/session/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::session::verification::evidence
