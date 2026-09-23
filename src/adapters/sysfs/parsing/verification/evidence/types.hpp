#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::parsing::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/parsing/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::parsing::verification::evidence
