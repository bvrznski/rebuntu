#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::process::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/process/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::process::verification::evidence
