#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::matching {
struct MatchingSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/matching";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::matching
