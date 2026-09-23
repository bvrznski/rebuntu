#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::assessment::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/assessment/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::assessment::contracts::errors
