#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::facts {
struct FactsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/facts";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::facts
