#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::network::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/network/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::network::verification::evidence
