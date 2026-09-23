#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::profile {
struct ProfileSkeleton final {
    static constexpr std::string_view path = "src/system/environment/profile";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::profile
