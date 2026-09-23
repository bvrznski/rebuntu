#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::category {
struct CategorySkeleton final {
    static constexpr std::string_view path = "src/core/errors/category";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::category
