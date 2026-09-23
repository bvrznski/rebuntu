#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::identity {
struct IdentitySkeleton final {
    static constexpr std::string_view path = "src/system/environment/identity";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::identity
