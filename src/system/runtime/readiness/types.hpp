#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::readiness {
struct ReadinessSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/readiness";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::readiness
