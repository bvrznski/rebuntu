#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::retriability {
struct RetriabilitySkeleton final {
    static constexpr std::string_view path = "src/core/errors/retriability";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::retriability
