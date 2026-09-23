#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::challenge {
struct ChallengeSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/challenge";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::challenge
