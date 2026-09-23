#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::cause {
struct CauseSkeleton final {
    static constexpr std::string_view path = "src/core/errors/cause";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::cause
