#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::connection::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/connection/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::connection::verification::evidence
